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


#ifndef _INCL_MYHDString_CPP
#define _INCL_MYHDString_CPP


namespace HDDBSF{
  class String{
  private:

      std::string mainData;

      std::string secureForStorage(const std::string &) const;
      std::string unpackFromStorage(const std::string &) const;

  public:
      String(const std::string & = "noData");
      void setMainData(const std::string &);
      std::string getMainData() const;
      long operator<(const String &) const;
      void loadFromString(const std::string&);
      std::string putIntoString() const;
  };
  std::string String::secureForStorage(const std::string & source) const{

      std::string scramble="j3kjljjkl1h89f3_";
      return SF::findAndReplace(source,"*!_",scramble);
  }
  std::string String::unpackFromStorage(const std::string & source) const{
      std::string scramble="j3kjljjkl1h89f3_";
      return SF::findAndReplace(source,scramble,"*!_");
  }

  String::String(const std::string & _mD){
      mainData=_mD;
  }

  void String::setMainData(const std::string &_mD){
      mainData=_mD;
  }
  std::string String::getMainData() const{
      return mainData;
  }
  long String::operator<(const String & _oth) const{
      if(mainData<_oth.mainData){
        return 1;
      }
      return 0;
  }
  void String::loadFromString(const std::string& s){

      std::string dataB="_string*!_";
      std::string dataE="_/string*!_";


      std::string d=s+dataB+"defaultData"+dataE;

      std::pair<std::string,int> res;
      long pos=0;
      res=SF::getNextString(d,pos,dataB,dataE);
      if(res.second==0){
        mainData= "notFound";
      }
      else{
        mainData= unpackFromStorage(res.first);
      }

  }
  std::string String::putIntoString() const{
    std::string dataB="_string*!_";
    std::string dataE="_/string*!_";


    std::string resString=dataB+secureForStorage(mainData)+dataE;

    return resString;
  }
}


#endif
