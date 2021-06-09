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


#ifndef _INCL_TEXTSWITHDIFFERENTVERSIONS_CPP
#define _INCL_TEXTSWITHDIFFERENTVERSIONS_CPP

namespace TWDVF{
  std::string eraseLeadingAndTrailingEmptyCharacters(const std::string &in){
    std::string output;
    long sz=in.size();
    while((sz>0)&&((in[sz-1]==' ')||(in[sz-1]=='\t')||(in[sz-1]=='\n')||(in[sz-1]=='\r'))){
      --sz;
    }
    long b=0;
    while((b<sz)&&((in[b]==' ')||(in[b]=='\t')||(in[b]=='\n')||(in[b]=='\r'))){
      ++b;
    }

    for(long i=b;i<sz;++i){
      output+=in[i];
    }
    return output;


  }
  std::vector<long> identifyVersions(const std::string & _input){
    std::set<long> allVs;
    long pos=0;
    std::pair<std::string,int> allD=SF::getNextString(_input,pos,"_v*","_");
    while(allD.second==1){
      if(BF::isNumeric(allD.first)){
        allVs.insert(BF::stringToInteger(allD.first));
      }
      allD=SF::getNextString(_input,pos,"_v*","_");
    }
    std::set<long>::const_iterator it=allVs.begin(),itE=allVs.end();
    std::vector<long> aV;
    aV.resize(allVs.size());
    long i=0;
    while(it!=itE){
      aV[i]=*it;++i;++it;
    }
    return aV;
  }
  std::pair<std::string,std::string> getSidesOfTheAssignment(const std::string & _a){
    std::pair<std::string, std::string> res;
    res.first=""; res.second="";
    std::string a=_a+"/= jkl";
    long pos=0;
    std::pair<std::string,int> allD=SF::getEverythingBefore(a,pos,"=");
    if(allD.second==0){
      return res;
    }
    res.first=allD.first;
    res.second=SF::getEverythingBefore(a,pos,"/=").first;
    return res;
  }
  std::pair<std::string,std::string> findVarThatEvaluates(const std::map<std::string,std::string> & _m){
    std::pair<std::string,std::string> next;
    next.first="";next.second="";
    std::map<std::string,std::string>::const_iterator it=_m.begin(),itE=_m.end();
    std::pair<double,int> tempEval;
    while((next.first=="")&&(it!=itE)){
      tempEval=FF::evFormula(it->second);
      if(tempEval.second==1){
        next.first=it->first;
        next.second=BF::doubleToString(tempEval.first);
      }
      ++it;
    }
    return next;
  }
  int isIndependent(const std::map<std::string,std::string> & _m, const std::string & _x){
    int ind=1;
    std::map<std::string,std::string>::const_iterator it=_m.begin(),itE=_m.end();
    long pos;
    std::pair<std::string,int> allD;
    while((ind==1)&&(it!=itE)){
      pos=0;
      allD=SF::getEverythingBefore(_x,pos,it->first);
      if(allD.second==1){
        ind=0;
      }
      ++it;
    }
    return ind;
  }
  std::pair<std::string,std::string> findIndependentVariable(const std::map<std::string,std::string> &_m){
    std::pair<std::string,std::string> next;
    next.first="";next.second="";
    std::map<std::string,std::string>::const_iterator it=_m.begin(),itE=_m.end();
    while((next.first=="")&&(it!=itE)){
      if(isIndependent(_m,it->second)){
        next.first=it->first;
        next.second=it->second;
      }
      ++it;
    }
    return next;
  }
  void performSearchReplace(std::map<std::string,std::string> & _m, std::string & _o,
                            const std::string & searchFor, const std::string &replaceWith){
    _m.erase(searchFor);
    std::map<std::string,std::string>::iterator it=_m.begin(),itE=_m.end();
    while(it!=itE){
      it->second= SF::findAndReplace(it->second,searchFor, replaceWith);
      ++it;
    }
    _o=SF::findAndReplace(_o,searchFor, replaceWith);

  }
  std::vector<std::string> getAssignmentVector(const std::string & manyLinesSeparatedBySeparators){
    std::vector<std::string> fR;
    std::string separator="@@";
    std::set<std::string> s;
    std::string scramble="!y&*!**_#?#?!";
    std::string input=manyLinesSeparatedBySeparators+separator+scramble+separator+scramble+separator;

    std::string oneLine="";
    long pos;
    std::pair<std::string,int> allD;
    pos=0;
    while(oneLine!=scramble){
      oneLine=eraseLeadingAndTrailingEmptyCharacters( SF::getEverythingBefore(input,pos,separator).first);
      if((oneLine!="")&&(oneLine!=scramble)){
        s.insert(oneLine);
      }
    }
    long sz=s.size();
    fR.resize(sz);
    std::set<std::string>::const_iterator it=s.begin(),itE=s.end();
    for(long i=0;i<sz;++i){
      fR[i]=*it;
      ++it;
    }
    return fR;
  }
  std::string singleVersion(const std::string & _input, const long & _v){
    std::string s_B="_?fRBegin?_";
    std::string s_E="_?fREnd?_";
    std::string s_Bi,s_Ei;
    long pos=0;
    std::pair<std::string,int> allD=SF::getNextString(_input,pos,s_B,s_E);
    if(allD.second==0){
      return _input;
    }
    std::string searchReplace=allD.first;

    std::vector<std::string> srAllVersions,srMyVersion;
    s_Bi="_v*a_";s_Ei="_/v*a_";
    srAllVersions=SF::getItems(_input,s_Bi,s_Ei);
    s_Bi="v*"+std::to_string(_v)+"_";s_Ei="_/"+s_Bi;s_Bi="_"+s_Bi;
    srMyVersion=SF::getItems(_input,s_Bi,s_Ei);

    std::map<std::string,std::string> allSearchReplacements;
    long sz,szv;
    std::pair<std::string,std::string> assignment;
    sz=srAllVersions.size();

    std::vector<std::string> assignmentVect;
    for(long i=0;i<sz;++i){
      assignmentVect=getAssignmentVector(srAllVersions[i]);
      szv=assignmentVect.size();
      for(long j=0;j<szv;++j){
        assignment=getSidesOfTheAssignment(assignmentVect[j]);
        allSearchReplacements[assignment.first]=assignment.second;
      }

    }
    sz=srMyVersion.size();
    for(long i=0;i<sz;++i){
      assignmentVect=getAssignmentVector(srMyVersion[i]);
      szv=assignmentVect.size();
      for(long j=0;j<szv;++j){
        assignment=getSidesOfTheAssignment(assignmentVect[j]);
        allSearchReplacements[assignment.first]=assignment.second;
      }

    }


    allD=SF::eraseStuffBetween(_input,s_B,s_E);
    std::string output=allD.first;


    // STEP 1: Formulas that can be evaluated
    std::pair<std::string,std::string> nextVar;
    nextVar.first=".";

    while(nextVar.first!="") {
      nextVar=findVarThatEvaluates(allSearchReplacements);
      if(nextVar.first!=""){
        performSearchReplace(allSearchReplacements,output,nextVar.first,nextVar.second);
      }
    }
    // STEP 2: Formulas that cannot be evaluated
    nextVar.first=".";
    while(nextVar.first!=""){
      nextVar=findIndependentVariable(allSearchReplacements);
      if(nextVar.first!=""){
        performSearchReplace(allSearchReplacements,output,nextVar.first,nextVar.second);
      }
    }


    return output;

  }
  std::string prepareProblemForTest(const std::string & _input, const long & _v){
    std::string output=singleVersion(_input,_v);
    long pos=0;
    std::pair<std::string,int> allD=SF::getNextString(output,pos,"_rA**|_", "_/rA**|_" );

    if(allD.second==1){
      std::string newStr="_rA**|_\n";
      std::vector<std::string> vectCh=SF::getItems(allD.first,"_rb*_","_/rb*_");
      std::vector<std::string> smst;
      std::sort(vectCh.begin(),vectCh.end());
      long sz=vectCh.size();
      for(long i=0;i<sz;++i){
        smst=SF::getItems(vectCh[i],"_vl*_", "_/vl*_");
        if(smst.size()>1){
          newStr+="_rb*_ _vl*_";
          newStr+=smst[0]+"_/vl*_ _vl*_<B>("+smst[0]+")</B> "+smst[1]+"_/vl*_ ";
          newStr+="_/rb*_\n";
        }

      }
      newStr+="_/rA**|_";
      pos=0;
      allD=SF::eraseStuffBetween(output,"_rA**|_", "_/rA**|_" );
      if(allD.second==1){
        output=allD.first+newStr;
      }
    }
    return output;
  }
}
#endif
