//    impwic-test : simple content management system
//
//    Copyright (C) 2021 Ivan Matic, https://impwic.com
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see https://www.gnu.org/licenses/.

#ifndef _INCL_MAINWEBSITEITIT_CPP
#define _INCL_MAINWEBSITEITIT_CPP
namespace MWID{

  class MainDB{
  public:
    std::set<std::string> tablesJustCreated;
    std::map<std::string,MTF::Table> dbsM;
    void initialize();
    void executeQueues();
    long numTexts() const;
    void putInitialDataInTable(const std::string &);
    MTF::Table createTableWithOneKey(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
    MTF::Table createTableWithTwoKeys(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
    std::string statusReportForDebugging() const;
  };
  std::string MainDB::statusReportForDebugging() const{
    std::string fR;
    std::map<std::string,MTF::Table>::const_iterator it;
    std::map<std::string,MTF::Table>::const_iterator itE;

    itE=dbsM.end();

    it=dbsM.begin();
    while(it!=itE){
      fR+="Size of "+it->first+" is "+std::to_string((it->second).size())+"\n";
      ++it;
    }

    it=dbsM.begin();
    while(it!=itE){
      fR+="\n\n"+it->first+" status report: \n";
      fR+=(it->second).statusReportForDebugging();
      ++it;
    }

    return fR;
  }


  long MainDB::numTexts() const{
    std::map<std::string,MTF::Table>::const_iterator it;
    it=dbsM.find("mainText");
    return (it->second).size();
  }
  MTF::Table MainDB::createTableWithOneKey(const std::string & _internalTableNickName,
                                                 const std::string & _folderName,
                                                 const std::string & _tabName,
                                                 const std::string & _key0,
                                                 const std::string & _mDN){
    MTF::Table tb;
    int tbCreated=tb.setFolderNames(_folderName);
    tb.setTableName(_tabName);
    std::vector<std::string> vKeys;
    vKeys.resize(1);
    vKeys[0]=_key0;
    tb.setKeyNames(vKeys);
    tb.setMainDataName(_mDN);
    if(tbCreated==1){
      tablesJustCreated.insert(_internalTableNickName);
    }
    return tb;
  }

  MTF::Table MainDB::createTableWithTwoKeys(const std::string & _internalTableNickName,
                                                  const std::string & _folderName,
                                                  const std::string & _tabName,
                                                  const std::string & _key0,
                                                  const std::string & _key1,
                                                  const std::string & _mDN){
    // Warning: _key0 must be alphabetically before _key1
    // Examples:
    //    1. _key0="alpha" _key1="beta".  This is OK
    //    2. _key0="alphaA" _key1="alphaB". This is also OK
    //    3. _key0="moon" _key1="mars". This is not OK, because "mars" would go before "moon" in a dictionary
    //
    MTF::Table tb;
    int tbCreated=tb.setFolderNames(_folderName);
    tb.setTableName(_tabName);
    std::vector<std::string> vKeys;
    vKeys.resize(2);
    vKeys[0]=_key0;
    vKeys[1]=_key1;


    tb.setKeyNames(vKeys);
    tb.setMainDataName(_mDN);
    if(tbCreated==1){
      std::vector<std::string> index;
      index.resize(1);
      index[0]=_key0;
      tb.createIndex(index);
      index[0]=_key1;
      tb.createIndex(index);
      tablesJustCreated.insert(_internalTableNickName);
    }
    return tb;
  }
  void MainDB::putInitialDataInTable(const std::string &_internalTableNickName){
    std::string tableName=dbsM[_internalTableNickName].getTableName();
    std::string fToInit=tableName;
    fToInit+=DD::GL_DBS.getInitExtension();
    fToInit+=".txt";
    std::string initCommands=IOF::fileToString(fToInit);
    if(initCommands!="fileNotFound"){
      std::vector<std::vector<std::string> > allCommands=SF::getCommands(initCommands, "_nextCommand!*!!_", "_/nextCommand!*!!_", "_n*!!***!_", "_/n*!!***!_");

      long sz=allCommands.size(),szIn;
      std::vector<std::string> kV;
      for(long i=0;i<sz;++i){

        szIn=allCommands[i].size();
        if(szIn>2){
          if(allCommands[i][0]=="insert"){
            kV.resize(szIn-2);
            for(long j=0;j<szIn-2;++j){
              kV[j]=allCommands[i][j+1];
            }
            dbsM[_internalTableNickName].insert(kV,allCommands[i][szIn-1]);
          }


        }
      }

    }

  }
  void MainDB::initialize(){
    IOF::sys_createFolderIfDoesNotExist(DD::GL_DBS.getMainFolder(),"readme.txt","Do not edit this folder");

    tablesJustCreated.clear();
    std::vector<std::string> vKeys;
    // main text initialization
    dbsM["mainText"]=createTableWithOneKey("mainText", DD::GL_DBS.getMainText(),"mainText","name","tData");
    executeQueues();
    if(!tablesJustCreated.empty()){
      std::set<std::string>::iterator it,itE;
      it=tablesJustCreated.begin();itE=tablesJustCreated.end();
      while(it!=itE){
        putInitialDataInTable(*it);
        ++it;
      }
    }

  }
  void MainDB::executeQueues(){
    std::map<std::string,MTF::Table>::iterator it;
    std::map<std::string,MTF::Table>::iterator itE;

    itE=dbsM.end();

    it=dbsM.begin();
    while(it!=itE){
      (it->second).executeFromQueue();
      ++it;
    }

  }
}
#endif
