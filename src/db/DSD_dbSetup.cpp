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

#ifndef _INCL_Setup_CPP
#define _INCL_Setup_CPP
namespace DSD{
  class Setup{
  private:

      std::string mfB="_mainFolderDB*!_";
      std::string mfE="_/mainFolderDB*!_";
      std::string eIdB="_externalIDDB*!_";
      std::string eIdE="_/externalIDDB*!_";
      std::string uNDBB="_usernameDB*!_";
      std::string uNDBE="_/usernameDB*!_";
      std::string hDBB="_hierarchy*!_";
      std::string hDBE="_/hierarchy*!_";
      std::string hCDBB="_hierarchyCache*!_";
      std::string hCDBE="_/hierarchyCache*!_";
      std::string cDBB="_countersDB*!_";
      std::string cDBE="_/countersDB*!_";
      std::string fDBB="_fileManagement*!_";
      std::string fDBE="_/fileManagement*!_";

      std::string messDBB="_messageManagement*!_";
      std::string messDBE="_/messageManagement*!_";

      std::string couasDBB="_couasManagement*!_";
      std::string couasDBE="_/couasManagement*!_";

      std::string mTBB="_mainText*!_";
      std::string mTBE="_/mainText*!_";
      std::string rPBB="_responseDB*!_";
      std::string rPBE="_/responseDB*!_";
      std::string staPBB="_statDB*!_";
      std::string staPBE="_/statDB*!_";

      std::string initTB="_initializerExtension*!_";
      std::string initTE="_/initializerExtension*!_";

      std::string sFSFB="_publicSubFolderToStoreFiles*!_";
      std::string sFSFE="_/publicSubFolderToStoreFiles*!_";

      std::string sFSFSysB="_publicSubFolderForSystemFiles*!_";
      std::string sFSFSysE="_/publicSubFolderForSystemFiles*!_";



      std::string st_chImB="_publicSubFolderToStoreChallengeImages*!_";
      std::string st_chImE="_/publicSubFolderToStoreChallengeImages*!_";
      std::string st_chAnB="_privateSubFolderToStoreChallengeAnswers*!_";
      std::string st_chAnE="_/privateSubFolderToStoreChallengeAnswers*!_";

      std::string nSSFIFB="_numStorageSubFoldersInFolder*!_";
      std::string nSSFIFE="_/numStorageSubFoldersInFolder*!_";
      std::string nFIFB="_numFilesInFolder*!_";
      std::string nFIFE="_/numFilesInFolder*!_";


      std::string default_extIdDB="mainFolderDB/externalIDDB";
      std::string default_mainFolder="mainFolderDB";
      std::string default_userNameDB="mainFolderDB/userNameDB";
      std::string default_hierarchy="mainFolderDB/hierarchyDB";
      std::string default_hCache="mainFolderDB/hierarchyCache";
      std::string default_counters="mainFolderDB/countersDB";
      std::string default_fManage="mainFolderDB/fileManDB";
      std::string default_messManage="mainFolderDB/messManDB";
      std::string default_couasManage="mainFolderDB/couasManDB";
      std::string default_mText="mainFolderDB/mainTextDB";
      std::string default_responseTable="mainFolderDB/responseDB";
      std::string default_statTable="mainFolderDB/statDB";
      std::string default_initExtension="_initFile";
      std::string default_publicStorage="q0";
      std::string default_publicSystemStorage="qs0";
      std::string default_challengeImages="c0";
      std::string default_challengeAnswers="mainFolderDB/a0";
      long default_numSubFolders=100;
      long default_numFilesInFolder=100;


      std::string mainFolder=default_mainFolder;

      std::string extIdDB=default_extIdDB;
      std::string userNameDB=default_userNameDB;
      std::string hierarchy=default_hierarchy;
      std::string counters=default_counters;
      std::string fManage=default_fManage;
      std::string messManage=default_messManage;
      std::string couasManage=default_couasManage;
      std::string mText=default_mText;
      std::string responseTable=default_responseTable;
      std::string statTable=default_statTable;
      std::string initExtension=default_initExtension;
      std::string hCache=default_hCache;
      std::string publicStorage=default_publicStorage;
      std::string publicSystemStorage=default_publicSystemStorage;
      std::string challengeImages=default_challengeImages;
      std::string challengeAnswers=default_challengeAnswers;
      long numSubFolders=default_numSubFolders;
      long numFilesInFolder=default_numFilesInFolder;

      std::string extIdDB_jN;
      std::string userNameDB_jN;
      std::string hierarchy_jN;
      std::string counters_jN;
      std::string fManage_jN;
      std::string messManage_jN;
      std::string couasManage_jN;
      std::string mText_jN;
      std::string responseTable_jN;
      std::string statTable_jN;
      std::string hCache_jN;
      std::string chIm_jN;
      std::string chAnsw_jN;


  public:




      void getSetupFromString(const std::string &);

      std::string getMainFolder() const;
      std::string getExternalIDDB() const;
      std::string getUserNameDB() const;
      std::string getHierarchy() const;
      std::string getHCache() const;
      std::string getCounters() const;
      std::string getFileManage() const;
      std::string getMessManage() const;
      std::string getCouasManage() const;
      std::string getMainText() const;
      std::string getResponseTable() const;
      std::string getStatTable() const;
      std::string getInitExtension() const;
      std::string printSetup() const;
      std::string getPublicStorage() const;
      std::string getPublicSystemStorage() const;
      std::string getChallengeImStorage() const;
      std::string getChallengeAnswStorage() const;
      long getNumSubFolders() const;
      long getNumFilesInFolder() const;


  };



  std::string Setup::getMainFolder() const{return mainFolder;}
  std::string Setup::getExternalIDDB() const{    return extIdDB; }
  std::string Setup::getUserNameDB() const{ return userNameDB;}
  std::string Setup::getHierarchy() const{return hierarchy;}
  std::string Setup::getCounters() const{return counters;}
  std::string Setup::getFileManage() const{return fManage;}
  std::string Setup::getMessManage() const{return messManage;}
  std::string Setup::getCouasManage() const{return couasManage;}
  std::string Setup::getMainText() const{return mText;}
  std::string Setup::getResponseTable() const{return responseTable;}
  std::string Setup::getStatTable() const{return statTable;}
  std::string Setup::getInitExtension() const{return initExtension;}
  std::string Setup::getHCache() const{return hCache;}
  std::string Setup::getPublicStorage() const{return publicStorage;}
  std::string Setup::getPublicSystemStorage() const{return publicSystemStorage;}
  std::string Setup::getChallengeImStorage() const{return challengeImages;}
  std::string Setup::getChallengeAnswStorage() const{return challengeAnswers;}
  long Setup::getNumSubFolders() const{return numSubFolders;}
  long Setup::getNumFilesInFolder() const{return numFilesInFolder;}


  void Setup::getSetupFromString(const std::string & fN){
      //std::string sSt=fileToString(fN);
      std::string sSt= fN ;
      sSt += mfB+default_mainFolder+mfE;
      sSt += eIdB+default_extIdDB+eIdE;
      sSt += uNDBB+default_userNameDB+uNDBE;
      sSt += hDBB+default_hierarchy+hDBE;
      sSt += hCDBB+default_hCache+hCDBE;
      sSt += cDBB+default_counters+cDBE;
      sSt += fDBB+default_fManage+fDBE;
      sSt += messDBB+default_messManage+messDBE;
      sSt += couasDBB+default_couasManage+couasDBE;
      sSt += mTBB+default_mText+mTBE;
      sSt += rPBB+default_responseTable+rPBE;
      sSt += staPBB+default_statTable+staPBE;
      sSt += initTB+ default_initExtension+initTE;
      sSt += sFSFB +default_publicStorage+sFSFE;
      sSt += sFSFSysB + default_publicSystemStorage+sFSFSysE;
      sSt += nSSFIFB+std::to_string(default_numSubFolders)+nSSFIFE;
      sSt += nFIFB+std::to_string(default_numFilesInFolder)+ nFIFE;
      sSt += st_chImB+default_challengeImages+st_chImE;
      sSt += st_chAnB+default_challengeAnswers+st_chAnE;


      long pos=0;
      mainFolder=(SF::getNextString(sSt,pos,mfB,mfE)).first;
      pos=0;
      extIdDB_jN=(SF::getNextString(sSt,pos,eIdB,eIdE)).first;
      extIdDB=mainFolder+"/"+extIdDB_jN;
      pos=0;
      userNameDB_jN=(SF::getNextString(sSt,pos,uNDBB,uNDBE)).first;
      userNameDB=mainFolder+"/"+userNameDB_jN;
      pos=0;
      hierarchy_jN=(SF::getNextString(sSt,pos,hDBB,hDBE)).first;
      hierarchy=mainFolder+"/"+hierarchy_jN;
      pos=0;
      hCache_jN=(SF::getNextString(sSt,pos,hCDBB,hCDBE)).first;
      hCache=mainFolder+"/"+hCache_jN;
      pos=0;
      counters_jN=(SF::getNextString(sSt,pos,cDBB,cDBE)).first;
      counters=mainFolder+"/"+counters_jN;
      pos=0;
      fManage_jN=(SF::getNextString(sSt,pos,fDBB,fDBE)).first;
      fManage=mainFolder+"/"+fManage_jN;
      pos=0;
      messManage_jN=(SF::getNextString(sSt,pos,messDBB,messDBE)).first;
      messManage=mainFolder+"/"+messManage_jN;
      pos=0;
      couasManage_jN=(SF::getNextString(sSt,pos,couasDBB,couasDBE)).first;
      couasManage=mainFolder+"/"+couasManage_jN;
      pos=0;
      mText_jN=(SF::getNextString(sSt,pos,mTBB,mTBE)).first;
      mText=mainFolder+"/"+mText_jN;
      pos=0;
      responseTable_jN=(SF::getNextString(sSt,pos,rPBB,rPBE)).first;
      responseTable=mainFolder+"/"+responseTable_jN;
      pos=0;
      statTable_jN=(SF::getNextString(sSt,pos,staPBB,staPBE)).first;
      statTable=mainFolder+"/"+statTable_jN;
      pos=0;
      chIm_jN=(SF::getNextString(sSt,pos,st_chImB,st_chImE)).first;
      challengeImages=chIm_jN;
      pos=0;
      chAnsw_jN=(SF::getNextString(sSt,pos,st_chAnB,st_chAnE)).first;
      challengeAnswers=mainFolder+"/"+chAnsw_jN;




      pos=0;
      initExtension=SF::getNextString(sSt,pos,initTB,initTE).first;

      pos=0;
      publicStorage=SF::getNextString(sSt,pos,sFSFB,sFSFE).first;

      pos=0;
      publicSystemStorage=SF::getNextString(sSt,pos,sFSFSysB,sFSFSysE).first;

      pos=0;
      numSubFolders=BF::stringToInteger(SF::getNextString(sSt,pos,nSSFIFB,nSSFIFE).first);
      pos=0;
      numFilesInFolder=BF::stringToInteger(SF::getNextString(sSt,pos,nFIFB,nFIFE).first);




  }
}

#endif
