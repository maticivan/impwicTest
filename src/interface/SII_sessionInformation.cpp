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


#ifndef _INCL_WI_SessionInformation_CPP
#define _INCL_WI_SessionInformation_CPP

namespace SII{
  class SessionInformation{
  private:
    std::string pageRequested;
    std::string passwordProvided;
    std::string newTextProvided;
    std::string pageToEdit;
    std::string correctPassword="impwic++";
    std::string header;
    std::string footer;
    std::string mainText;
    long indicatorInitialized;
    long indicatorFormResponded;
    std::vector<std::string> envVariables;

  public:
    SessionInformation();
    int initSession(const cgicc::Cgicc & );
    long isInitialized() const;



    void analyzeEnvVarsAndForms(const cgicc::Cgicc &);

    long isFormResponded() const;

    std::string preparePage();

  };
  std::string SessionInformation::preparePage(){
    return header+mainText+footer;
  }
  SessionInformation::SessionInformation(){
    header=IOF::fileToString("htmlHeader.txt");
    footer=IOF::fileToString("htmlFooter.txt");
    indicatorInitialized=0;
    indicatorFormResponded=0;
    passwordProvided="";
    pageRequested="firstPage";
    newTextProvided="";
    pageToEdit="none";
  }

  void SessionInformation::analyzeEnvVarsAndForms(const cgicc::Cgicc & ch){
    indicatorFormResponded=0;


    if((envVariables[13]=="GET")||(envVariables[13]=="POST")){
      if(envVariables[13]=="POST"){indicatorFormResponded=1;}



      cgicc::const_form_iterator it, itE;
      itE = ch.getElements().end();
      it=ch.getElements().begin();
      while(it!=itE){
        if(it->getName()=="page"){
          pageRequested=it->getValue();
        }
        if(it->getName()=="password"){
          passwordProvided=it->getValue();
        }
        if(it->getName()=="textContent"){
          newTextProvided=it->getValue();
        }
        if(it->getName()=="pToEdit"){
          pageToEdit=it->getValue();
        }
        ++it;
      }
    }
  }

  int SessionInformation::initSession(const cgicc::Cgicc & ch){
    if(indicatorInitialized==0){
      envVariables=BI::getEnvVars();
      analyzeEnvVarsAndForms(ch);
      std::vector<std::string> k,v;
      std::vector< std::pair<std::vector<std::string>, std::string> > searchRes;
      if((indicatorFormResponded==1) &&  (newTextProvided=="delete") && (passwordProvided==correctPassword) ){
        // deleting text
        k.resize(1);v.resize(1);
        k[0]="name";
        v[0]=pageToEdit;
        searchRes=DD::GL_MAIN_DB.dbsM["mainText"].search(v,k);
        if(searchRes.size()>0){
          DD::GL_MAIN_DB.dbsM["mainText"].delRow(searchRes[0].first);
          return 1;
        }
        return 0;
      }
      if((indicatorFormResponded==1) && (passwordProvided==correctPassword) ){
        // inserting text
        k.resize(1);v.resize(1);
        k[0]="name";
        v[0]=pageToEdit;
        searchRes=DD::GL_MAIN_DB.dbsM["mainText"].search(v,k);
        DD::GL_MAIN_DB.dbsM["mainText"].insert(searchRes[0].first,newTextProvided);
        return 1;
      }
      mainText="Page Not Found";
      k.resize(1);v.resize(1);
      k[0]="name";
      v[0]=pageRequested;
      searchRes=DD::GL_MAIN_DB.dbsM["mainText"].search(v,k);
      if(searchRes.size()>0){
        mainText=searchRes[0].second;
      }
    }
    indicatorInitialized=1;
    return indicatorInitialized;
  }
  long SessionInformation::isInitialized() const{return indicatorInitialized;}
  long SessionInformation::isFormResponded() const{return indicatorFormResponded;}
}
#endif
