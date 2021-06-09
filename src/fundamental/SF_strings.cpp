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


#ifndef _INCL_SF_STRINGS_CPP
#define _INCL_SF_STRINGS_CPP


namespace SF{


  template<class T1, class T2>
  class TwoValues{
  public:
    T1 x;
    T2 y;
    long operator<(const TwoValues &) const;
  };
  template<class T1, class T2>
  long TwoValues<T1,T2>::operator<(const TwoValues<T1,T2> & oth) const{
    if(x<oth.x){
      return 1;
    }
    if(x>oth.x){
      return 0;
    }
    if(y<oth.y){
      return 1;
    }
    return 0;
  }

  template<typename T1, typename T2>
  void sortWithFollower(std::vector<T1> & v1, std::vector<T2> & v2){

    long sz=v1.size();
    if(v2.size()==sz){
      std::vector<TwoValues<T1,T2> > w;
      w.resize(sz);
      for(long i=0;i<sz;++i){
        (w[i]).x=v1[i];
        (w[i]).y=v2[i];
      }
      std::sort(w.begin(),w.end());
      for(long i=0;i<sz;++i){
        v1[i]=(w[i]).x;
        v2[i]=(w[i]).y;
      }
    }
  }

  char toLowerCase(const char & x){
      char fR=x;
      if((x>='A')&&(x<='Z')){
          fR=fR-'A'+'a';
      }
      return fR;
  }
  std::string toLowerCase(const std::string & input){
      std::string output=input;
      long len = input.length();
      for(long i=0;i<len;++i){
          output[i]=toLowerCase(input[i]);
      }
      return output;
  }


  std::pair<std::string, int> getEverythingBefore(const std::string & memblock,
                                                  long & pos,
                                                  const std::string &endSt,
                                                  const int & caseSensitive = 0){
      long size=memblock.length();
      std::string fR="";
      long endingLen=endSt.length();
      std::string stToAdd="";
      long posInEnd=0;
      char currentCh;
      char compareCh;
      while ((pos<size) &&(posInEnd<endingLen ) ){
          currentCh=memblock[pos];
          compareCh=endSt[posInEnd];
          if(caseSensitive==0){
              currentCh=toLowerCase(currentCh);
              compareCh=toLowerCase(compareCh);
          }

          stToAdd+= memblock[pos];
          if(currentCh==compareCh){
              ++posInEnd;
          }
          else{


              pos-=stToAdd.length();
              ++pos;
              fR+=stToAdd[0];
              posInEnd=0;
              stToAdd="";


          }
          ++pos;
      }
      int success=0;
      if(posInEnd==endingLen){
          success=1;
      }

      return std::make_pair(fR,success);
  }

  long firstContainsTheOther(const std::string &st1,const std::string &st2,const int & caseSensitive=0){
    long pos=0;
    std::pair<std::string,int> aD=getEverythingBefore(st1,pos,st2,caseSensitive);
    return aD.second;
  }

  std::pair<std::string,int> getNextString(const std::string &  ,
                                           long &  ,
                                           const std::string & ,
                                           const std::string & ,
                                           const int &  );

  std::pair<std::string,int> gNextStrStrong(const std::string & memblock,
                                           long & pos,
                                           const std::string &startString,
                                           const std::string &endString,
                                           const int & caseSensitive = 0){
      if(startString==endString){
        return getNextString(memblock,pos,startString,endString,caseSensitive);
      }
      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;


      std::pair<std::string,int> thrashSt=getEverythingBefore(memblock,pos,startString,caseSensitive);
      std::pair<std::string,int> beforeNextStart,beforeNextEnd;
      if(thrashSt.second==1){
          long depth=1;
          long posAfterStart;
          long posAfterEnd;
          while(depth>0){
            posAfterStart=pos;
            posAfterEnd=pos;
            beforeNextStart=getEverythingBefore(memblock,posAfterStart,startString,caseSensitive);
            beforeNextEnd=getEverythingBefore(memblock,posAfterEnd,endString,caseSensitive);
            if((beforeNextStart.second==1)&&(beforeNextEnd.second==1)){
              if(posAfterStart<posAfterEnd){
                fR.first+=beforeNextStart.first+startString;
                pos=posAfterStart;
                ++depth;
              }
              else{
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
            }
            else{
              if(beforeNextEnd.second==1){
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
              else{
                fR.second=0;
                fR.first="";
                return fR;
              }
            }
          }
          fR.second=1;

      }

      if(fR.second==0){
          fR.first="";
      }
      return fR;
  }

  std::pair<std::string,int> getNextString(const std::string & memblock,
                                           long & pos,
                                           const std::string &startString,
                                           const std::string &endString,
                                           const int & caseSensitive = 0){

      if(startString!=endString){
        return gNextStrStrong(memblock,pos,startString,endString,caseSensitive);
      }

      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;


      std::pair<std::string,int> thrashSt=getEverythingBefore(memblock,pos,startString,caseSensitive);

      if(thrashSt.second==1){
          fR=getEverythingBefore(memblock,pos,endString,caseSensitive);
      }
      if(fR.second==0){
          fR.first="";
      }
      return fR;
  }
  std::pair<std::string,int> replaceNextString(const std::string &  ,
                                               long &  ,
                                               const std::string & ,
                                               const std::string & ,
                                               const int &  ,
                                               const std::string &  );

  std::pair<std::string,int> rNextStrStrong(const std::string & memblock,
                                            long & pos,
                                            const std::string &startString,
                                            const std::string &endString,
                                            const int & caseSensitive = 0,
                                            const std::string & replaceWith=""){
      if(startString==endString){
        return replaceNextString(memblock,pos,startString,endString,caseSensitive,replaceWith);
      }
      std::pair<std::string,int> fR;
      fR.first="";
      fR.second=0;



      std::pair<std::string,int> thrashSt=getEverythingBefore(memblock,pos,startString,caseSensitive);

      std::pair<std::string,int> beforeNextStart,beforeNextEnd;

      if(thrashSt.second==1){
          long depth=1;
          long posAfterStart;
          long posAfterEnd;
          while(depth>0){
            posAfterStart=pos;
            posAfterEnd=pos;
            beforeNextStart=getEverythingBefore(memblock,posAfterStart,startString,caseSensitive);
            beforeNextEnd=getEverythingBefore(memblock,posAfterEnd,endString,caseSensitive);
            if((beforeNextStart.second==1)&&(beforeNextEnd.second==1)){
              if(posAfterStart<posAfterEnd){
                fR.first+=beforeNextStart.first+startString;
                pos=posAfterStart;
                ++depth;
              }
              else{
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
            }
            else{
              if(beforeNextEnd.second==1){
                --depth;
                fR.first+=beforeNextEnd.first;
                if(depth>0){
                  fR.first+=endString;
                }
                pos=posAfterEnd;
              }
              else{
                fR.second=0;
                fR.first="";
                return fR;
              }
            }
          }
          fR.second=1;

      }

      if(fR.second==0){
          fR.first=memblock;
          return fR;
      }
      fR.first=thrashSt.first;
      fR.first+=replaceWith;
      long posSave=(fR.first).length();
      long sz=memblock.length();
      while(pos<sz){
        fR.first += memblock[pos];
        ++pos;
      }
      pos=posSave;


      return fR;
  }

  std::pair<std::string,int> replaceNextString(const std::string & memblock,
                                               long & pos,
                                               const std::string &startString,
                                               const std::string &endString,
                                               const int & caseSensitive = 0,
                                               const std::string & replaceWith=""){
    if(startString!=endString){
      return rNextStrStrong(memblock,pos,startString,endString,caseSensitive,replaceWith);
    }

    std::pair<std::string,int> fR;
    fR.first="";
    fR.second=0;


    std::pair<std::string,int> thrashSt=getEverythingBefore(memblock,pos,startString,caseSensitive);

    if(thrashSt.second==1){
        fR=getEverythingBefore(memblock,pos,endString,caseSensitive);
    }
    if(fR.second==0){
        fR.first="";
        return fR;
    }
    fR.first=thrashSt.first;
    fR.first+=replaceWith;
    long posSave=(fR.first).length();
    long sz=memblock.length();
    while(pos<sz){
      fR.first += memblock[pos];
      ++pos;
    }
    pos=posSave;
    return fR;
  }
  std::pair<std::string,int> eraseStuffBetween(const std::string & memblock,
                                               const std::string &startString,
                                               const std::string &endString,
                                               const long & cpos = 0,
                                               const int & caseSensitive = 0){

      long pos=cpos;
      return replaceNextString(memblock,pos,startString,endString,caseSensitive,"");
  }
  std::string replaceVariablesWithValues(const std::string & input,
                                         const std::string & sepVarB, const std::string & sepVarE,
                                         const std::map<std::string,std::string> & varsToVals){
    std::string output=input;
    std::string currentVar,currentVal;
    long sepLens=sepVarB.length()+sepVarE.length();
    long currentValLen;
    std::map<std::string,std::string>::const_iterator it,itE;
    itE=varsToVals.end();
    long pos;
    std::pair<std::string,int> allD;
    pos=0;allD=getNextString(output,pos,sepVarB,sepVarE);
    std::string newOutput;
    while(allD.second==1){
      currentVar=allD.first;
      it=varsToVals.find(currentVar);
      if(it!=itE){

        pos-=(sepLens+currentVar.length());
        if(pos<0){pos=0;}
        newOutput="";
        for(long i=0;i<pos;++i){
          newOutput+=output[i];
        }
        currentVal=it->second;
        allD=replaceNextString(output,pos,sepVarB,sepVarE,1,currentVal);
        if(allD.second==1){
          output=newOutput+allD.first;
        }
      }
      allD=getNextString(output,pos,sepVarB,sepVarE);
    }
    return output;
  }

  template<typename T>
  void flipTheStack(std::stack<T>& s){
    std::stack<T> t;
    t=std::move(s);
    while(!t.empty()){
      s.push(t.top());
      t.pop();
    }
  }

  template<typename TTT>
  std::set<TTT> vectorToSet(const std::vector<TTT> &_v){
    std::set<TTT> fR;
    long sz=_v.size();
    for(long i=0;i<sz;++i){
      fR.insert(_v[i]);
    }
    return fR;
  }


  std::string findAndReplace(const std::string &input,
                          const std::string &_searchFor,
                          const std::vector<std::string> &_replaceWith,
                          const int &all=1,
                          const int &caseSensitive=0){
      // Searches input for _searchFor; The first one is replaced by _replaceWith[0],
      // the second occurrence with _replaceWith[1], ..., the _replaceWith.size()-th ocurrence
      // with _replaceWith[0] again and it cycles

      std::string searchFor=_searchFor;
      std::vector<std::string> replaceWith=_replaceWith;
      if(replaceWith.size()==0){
        replaceWith.resize(1);replaceWith[0]="";
      }
      long ctrReplaceWith=0;
      long lenReplW=replaceWith.size();
      std::string endS="e!*&!##%&$!_++R3!a";
      long pos=0;
      std::pair<std::string,int> allD;
      std::string output="",nBefore;
      long len=input.length();
      long lsf=searchFor.length();
      long lp1=len+1;
      long oldPos;
      while(pos<len){
        oldPos=pos;
        allD=getEverythingBefore(input,pos,searchFor,caseSensitive);
        if(allD.second==1){
          output += allD.first;
          if(pos<lp1){
            //Found the real occurrence of searchFor
            // not the fake one that we added to the end
            output+=replaceWith[ctrReplaceWith];
            if(lenReplW>1){
              ++ctrReplaceWith;
              if(ctrReplaceWith==lenReplW){
                ctrReplaceWith=0;
              }
            }
            if(all==0){
              searchFor=searchFor+endS;
            }
          }
        }
        else{
          pos=len;
          for(long i=oldPos;i<pos;++i){
            output+=input[i];
          }
        }

      }
      return output;
  }

  std::string findAndReplace(const std::string &input,
                          const std::string &searchFor,
                          const std::string &_replaceWith,
                          const int &all=1,
                          const int &caseSensitive=0){

      if(searchFor==_replaceWith){
        return input;
      }
      std::vector<std::string> replw;
      replw.resize(1);
      replw[0]=_replaceWith;
      return findAndReplace(input,searchFor,replw,all,caseSensitive);
  }


  long countInString(const std::string & _allItems,
                                    const std::string & _nextB="_n_",
                                    const std::string & _nextE="_/n_",
                                    const std::string & _attMustHave="!*!"){
    long fR=0;
    long pos=0;
    std::pair<std::string,int> nextSt=getNextString(_allItems,pos,_nextB,_nextE);
    while(nextSt.second==1){
      if(_attMustHave!="!*!"){
        fR+=firstContainsTheOther(nextSt.first,_attMustHave);
      }
      else{
        ++fR;
      }
      nextSt=getNextString(_allItems,pos,_nextB,_nextE);
    }
    return fR;
  }
  std::string vectorToString(const std::vector<std::string> & v,
                            const std::string & _nextB="_n_",
                            const std::string & _nextE="_/n_"){
    std::string fR="";
    long sz=v.size();
    for(long i=0;i<sz;++i){
      fR+=_nextB+v[i]+_nextE;
    }
    return fR;
  }
  std::vector<std::string> getItems(const std::string & _allItems,
                                                          const std::string & _nextB="_n_",
                                                          const std::string & _nextE="_/n_",
                                                          const std::string & _attMustHave="!*!"){
    std::vector<std::string> fR;
    long sz,szAll;
    sz=countInString(_allItems,_nextB,_nextE);
    szAll=sz;
    if(_attMustHave!="!*!"){
      sz=countInString(_allItems,_nextB,_nextE,_attMustHave);
    }

    if(sz==0){
      return fR;
    }
    fR.resize(sz);
    long pos=0;
    std::string nextSt;
    long j=0,i;
    for(i=0;i<szAll;++i){
        nextSt= getNextString(_allItems,pos,_nextB,_nextE).first;
        if(_attMustHave=="!*!"){
          fR[i]=nextSt;
        }
        else{
          if(firstContainsTheOther(nextSt,_attMustHave)==1){
            fR[j]=nextSt;++j;
          }
        }

    }

    return fR;
  }

  std::vector<std::vector<std::string> > getCommands(const std::string & _qs,
                                                                    const std::string & _nextB,
                                                                    const std::string & _nextE,
                                                                    const std::string & _sepInsideB,
                                                                    const std::string & _sepInsideE){
    std::vector<std::vector<std::string> > fR;

    long sz=countInString(_qs,_nextB,_nextE);
    if(sz==0){
      return fR;
    }
    fR.resize(sz);
    long pos=0;
    std::string individualLine;
    for(long i=0;i<sz;++i){
      individualLine=getNextString(_qs,pos,_nextB,_nextE).first;
      fR[i]=getItems(individualLine,_sepInsideB,_sepInsideE);
    }
    return fR;

  }


  std::string removeInfoAndPrepareNew(std::string &oldSysData, const std::string & _bS, const std::string & _eS, const std::string & _nD){
    std::string nD=_bS+_nD+_eS;
    long pos=0;
    std::pair<std::string, int> allD=eraseStuffBetween(oldSysData,_bS,_eS,pos);
    if(allD.second==1){
      oldSysData=allD.first;
    }
    return nD;
  }



  long getLegalCharacters(std::map<char,long> &fR1, std::map<long,char> &fR2){
   char c;
   long toAdd=0;
   for(c='0';c<='9';++c){
     fR1[c]=toAdd;
     fR2[toAdd]=c;
     ++toAdd;
   }
   for(c='a';c<='z';++c){
     fR1[c]=toAdd;
     fR2[toAdd]=c;
     ++toAdd;
   }
   for(c='A';c<='Z';++c){
     fR1[c]=toAdd;
     fR2[toAdd]=c;
     ++toAdd;
   }

   return toAdd;
  }

  class TranslatorCharToLong{
  private:
    long num;
    std::map<char,long> cToL;
    std::map<long,char> lToC;
  public:
    TranslatorCharToLong();
    long getLong(const char &) const;
    char getChar(const long &) const;
    long getNum() const;
  };
  TranslatorCharToLong::TranslatorCharToLong(){
    num=getLegalCharacters(cToL,lToC);
  }
  long TranslatorCharToLong::getLong(const char & _c) const{
    std::map<char,long>::const_iterator it,itE;
    itE=cToL.end();
    it=cToL.find(_c);
    long fR=-1;
    if(it!=itE){
      fR=it->second;
    }
    return fR;
  }
  char TranslatorCharToLong::getChar(const long & _l) const{
    std::map<long,char>::const_iterator it,itE;
    itE=lToC.end();
    it=lToC.find(_l);
    char fR='0';
    if(it!=itE){
      fR=it->second;
    }
    return fR;
  }
  long TranslatorCharToLong::getNum() const{
    return num;
  }
  TranslatorCharToLong GLOBAL_TRANSLATOR_CHAR_LONG;
  long charToNum(const char & x){
    return GLOBAL_TRANSLATOR_CHAR_LONG.getLong(x);
  }
  std::string numToStr(const long & _l){
    long l=_l%256;
    std::string fR="a";
    char c=GLOBAL_TRANSLATOR_CHAR_LONG.getChar(l);
    fR[0]=c;
    return fR;
  }

  std::vector<long> strToVectInt(const std::string &_s){
    std::vector<long> fR;
    long sz=_s.size();
    fR.resize(sz);
    long i=0;
    while(i<sz){
      fR[i]= charToNum(_s[i]);
    //  fR[i]=_s[i]-'0';
      ++i;
    }
    return fR;
  }


  std::string vectIntToStr(const std::vector<long> &_c){
    long i=0;
    long lC=_c.size();
    std::string c;
    while(i<lC){
      c+=numToStr(_c[i]);
      //c+=std::to_string(_c[i]);
      ++i;
    }
    return c;
  }
  std::vector<long> getAdditionVector6(){
    std::vector<long> aV6;
    aV6.resize(6);
    aV6[0]=7;aV6[1]=9;aV6[2]=3;aV6[3]=8;aV6[4]=7;aV6[5]=4;
    return aV6;
  }

  std::string combineTwoWords(const std::string &_a, const std::string &_b){

    // lengths of _a and _b must be smaller than or equal to 999
    long numChr=GLOBAL_TRANSLATOR_CHAR_LONG.getNum();
    std::vector<long> aV6=getAdditionVector6();
    std::string __c;
    std::string __b=_b;
    if(__b.length()<3){
      __b="000"+__b;
    }
    std::string __a=_a;
    if(__a.length()<3){
      __a="000"+__a;
    }
    std::vector<long> a,b;
    a=strToVectInt(__a);b=strToVectInt(__b);
    std::vector<long> c;
    long lA,lB,lC;
    lA=a.size();lB=b.size();
    std::string __slA=BF::padded(lA,100,"0");
    std::string __slB=BF::padded(lB,100,"0");
    std::vector<long> slA=strToVectInt(__slA);
    std::vector<long> slB=strToVectInt(__slB);
    lC=lA+lB+6;
    c.resize(lC);
    long i=1;
    c[0]=(a[0]+b[0])%numChr;
    while(i<3){
      c[i]=(a[i]+b[i]+c[i-1])%numChr;++i;
    }
    c[3]=(c[2]+c[1]+slA[0]+aV6[0])%numChr;
    c[4]=(c[3]+c[1]+slB[0]+aV6[1])%numChr;
    c[5]=(c[4]+c[1]+slA[1]+aV6[2])%numChr;
    c[6]=(c[5]+c[1]+slB[1]+aV6[3])%numChr;
    c[7]=(c[6]+c[1]+slA[2]+aV6[4])%numChr;
    c[8]=(c[7]+c[1]+slB[2]+aV6[5])%numChr;
    i=9;
    long posB=lB;
    while(posB>0){
      --posB;
      c[i]=(c[i-1]+b[posB])%numChr;
      ++i;
    }
    posB=3;
    long posA=3;
    while(posA<lA){
      c[i]=(c[i-1]+b[posB]+a[posA])%numChr;
      ++i;++posA;++posB;
      if(posB>=lB){
        posB=0;
      }

    }
    return vectIntToStr(c);
  }
  long makeItBiggerThanOrEqual0(long x){
    long numChr=GLOBAL_TRANSLATOR_CHAR_LONG.getNum();
    while(x<0){
      x+=numChr;
    }
    return x;
  }
  std::pair<std::string,std::string> oneWordToTwoWords(const std::string &_st){
    std::vector<long> aV6=getAdditionVector6();
    long lenC=_st.length();
    if(lenC<9){
      return std::pair<std::string,std::string>("notFound","notFound");
    }
    std::string __a,__b;
    std::vector<long> a,b,c,slA,slB;

    c=strToVectInt(_st);
    slA.resize(3);slB.resize(3);

    slA[0]=makeItBiggerThanOrEqual0(c[3]-c[2]-c[1]-aV6[0]);
    slB[0]=makeItBiggerThanOrEqual0(c[4]-c[3]-c[1]-aV6[1]);
    slA[1]=makeItBiggerThanOrEqual0(c[5]-c[4]-c[1]-aV6[2]);
    slB[1]=makeItBiggerThanOrEqual0(c[6]-c[5]-c[1]-aV6[3]);
    slA[2]=makeItBiggerThanOrEqual0(c[7]-c[6]-c[1]-aV6[4]);
    slB[2]=makeItBiggerThanOrEqual0(c[8]-c[7]-c[1]-aV6[5]);
    long lA,lB;
    lA=BF::stringToInteger(vectIntToStr(slA));
    lB=BF::stringToInteger(vectIntToStr(slB));
    long posC=9;
    long posB=lB;
    a.resize(lA);b.resize(lB);
    while(posB>0){
      --posB;
      b[posB]=makeItBiggerThanOrEqual0(c[posC]-c[posC-1]);
      ++posC;
    }
    long posA=3;
    posB=3;
    a[0]=makeItBiggerThanOrEqual0(c[0]-b[0]);
    a[1]=makeItBiggerThanOrEqual0(c[1]-c[0]-b[1]);
    a[2]=makeItBiggerThanOrEqual0(c[2]-c[1]-b[2]);
    while(posA<lA){
      a[posA]=makeItBiggerThanOrEqual0(c[posC]-c[posC-1]-b[posB]);
      ++posA;++posC;++posB;
      if(posB>=lB){
        posB=0;
      }
    }
    __a=vectIntToStr(a);
    __b=vectIntToStr(b);
    return std::pair<std::string,std::string>(__a,__b);
  }
  std::string getElFromMapOrNotFoundMessage(const std::map<std::string,std::string> & _mm, const std::string & _q, const std::string & _mnf){
    std::map<std::string,std::string>::const_iterator it,itE=_mm.end();
    it=_mm.find(_q);
    if(it!=itE){
      return it->second;
    }
    return _mnf;
  }

  std::vector<std::string> removeFromSeq(const std::vector<std::string> &in, const std::string & toRemove){
    std::vector<std::string> out;
    long sz=in.size();
    long i=0;
    while((i<sz)&&(in[i]!=toRemove)){
      ++i;
    }
    if(i==sz){
      return in;
    }
    out.resize(sz-1);
    if(sz==1){
      return out;
    }
    for(long j=0;j<i;++j){
      out[j]=in[j];
    }
    ++i;
    while(i<sz){
      out[i-1]=in[i];
    }
    return out;
  }
  void varValPairs(const std::string & input,
                                                const std::string & sepVarValB, const std::string & sepVarValE,
                                                const std::string & sepVarB,const std::string & sepVarE,
                                                const std::string & sepValB, const std::string &sepValE,
                                                std::map<std::string,std::string> & mM){
    std::vector<std::string> indItems=getItems(input,sepVarValB,sepVarValE);
    long sz=indItems.size();
    long pos;std::pair<std::string,int> allD;
    std::string val,var;
    for(long i=0;i<sz;++i){
      pos=0;allD=getNextString(indItems[i],pos,sepVarB,sepVarE);
      if(allD.second==1){
        var=allD.first;
        pos=0;allD=getNextString(indItems[i],pos,sepValB,sepValE);
        if(allD.second==1){
          val=allD.first;
          mM[var]=val;
        }
      }
    }
  }



  std::string massiveFiRepl(const std::string &input, const std::vector<std::pair<std::string, std::string> > & v, const int & caseSensitive){
    std::string output=input;
    long sz=v.size();
    for(long i=0;i<sz;++i){
      output=findAndReplace(output,v[i].first,v[i].second,1,caseSensitive);
    }

    return output;
  }
  std::string massiveFiReplReverse(const std::string &input, const std::vector<std::pair<std::string, std::string> > & v, const int & caseSensitive){
    std::string output=input;
    long sz=v.size();
    for(long i=0;i<sz;++i){
      output=findAndReplace(output,v[i].second,v[i].first,1,caseSensitive);
    }

    return output;
  }

  std::pair<std::string,int> replaceAllOuterLayerSeparators(const std::string &input,
                                                            const std::string & _cOpen,
                                                            const std::string &_cClose,
                                                            const std::string & _rOpen,
                                                            const std::string &_rClose,
                                                            const std::vector<std::pair<std::string,std::string> > & permanentChangesForProtection ,
                                                            const int & caseSensitive =0){
    std::string output="";
    std::pair<std::string,int> fR;fR.second=1;
    long pos=0,oldPos,newPos;
    std::pair<std::string,int> allD,allDB;
    allD=getNextString(input,pos,_cOpen,_cClose,caseSensitive);
    if(allD.second==0){
      fR.first=input;
      return fR;
    }
    oldPos=0;
    int keepGoing=1;
    std::string replacingPart;
    long szV=permanentChangesForProtection.size();
    while(keepGoing==1){
      replacingPart= allD.first;
      if(szV>0){
        replacingPart=massiveFiRepl(replacingPart,permanentChangesForProtection,caseSensitive);
      }
      allDB=getEverythingBefore(input,oldPos,_cOpen,caseSensitive);
      if(allDB.second==1){
        output+=allDB.first;
        output+=_rOpen+replacingPart+_rClose;
        oldPos=pos;
        allD=getNextString(input,pos,_cOpen,_cClose,caseSensitive);
        if(allD.second==0){
          keepGoing=0;
        }
      }
      else{
        fR.second=0;keepGoing=0;
      }

    }
    long ln=input.length();
    while(oldPos<ln){
      output+=input[oldPos];
      ++oldPos;
    }
    fR.first=output;
    return fR;

  }


  std::set<std::string> stringToSet(const std::string & everything, const std::string & sepKeyB,const std::string & sepKeyE){
    std::set<std::string> fR;
    std::vector<std::string> keys=getItems(everything,sepKeyB,sepKeyE);
    long sz=keys.size();
    for(long i=0;i<sz;++i){
      fR.insert(keys[i]);
    }
    return fR;
  }
  std::string setToString(const std::set<std::string> & s, const std::string & sepKeyB,const std::string & sepKeyE ,const std::string &formattingSeparator=""){
    std::string fR="";
    std::set<std::string>::const_iterator it=s.begin(),itE=s.end();
    while(it!=itE){
      fR+=sepKeyB+(*it)+sepKeyE+formattingSeparator;
      ++it;
    }
    return fR;
  }
  std::map<std::string,std::string> stringToMap(const std::string & everything, const std::string & sepKeyB,const std::string & sepKeyE,const std::string & sepValB,const std::string & sepValE){
    std::map<std::string,std::string> fR;
    std::vector<std::string> keys=getItems(everything,sepKeyB,sepKeyE);
    std::vector<std::string> vals=getItems(everything,sepValB,sepValE);
    long szK=keys.size();
    long szV=vals.size();
    long sz=szK;
    if(sz>szV){sz=szV;}
    for(long i=0;i<sz;++i){
      fR[keys[i]]=vals[i];
    }

    return fR;
  }
  std::string mapToString(const std::map<std::string,std::string> & m, const std::string & sepKeyB,const std::string & sepKeyE,const std::string & sepValB,const std::string & sepValE,const std::string &formattingSeparator=""){
    std::string fR="";
    std::map<std::string,std::string>::const_iterator it=m.begin(),itE=m.end();
    while(it!=itE){
      fR+=sepKeyB+(it->first)+sepKeyE+sepValB+(it->second)+sepValE+formattingSeparator;
      ++it;
    }
    return fR;
  }
  std::string updateVarsWithVals(const std::string & input, const std::map<std::string,std::string> & sr, const std::string & sB, const std::string &sE){
    std::string output=input;
    std::map<std::string,std::string>::const_iterator it,itE;
    it=sr.begin();itE=sr.end();
    while(it!=itE){
      output=findAndReplace(output,sB+(it->first)+sE,sB+(it->second)+sE);
      ++it;
    }
    return output;
  }
  template<typename TTT>
  std::vector<TTT> oneElementVector(const TTT& el){
    std::vector<TTT> fR;fR.resize(1);fR[0]=el;
    return fR;
  }
  template<typename TTT>
  std::stack<TTT> clearStack(std::stack<TTT> & v){
    if(v.empty()){
      return v;
    }
    v.pop();
    return clearStack(v);
  }
  template<typename TTT>
  std::vector<TTT> stackToVector(std::stack<TTT> & st){
    std::vector<TTT> fR;
    long sz=st.size();
    if(sz>0){
      fR.resize(sz);
      for(long i=0;i<sz;++i){
        fR[sz-i-1]=st.top();
        st.pop();
      }
    }
    return fR;
  }

  std::string incrementString(const std::string & x){

      std::string res=x;
      long cS=res.size();
      long success=0;--cS;
      char zeroM1='0'-1;
      char nineP1='9'+1;
      char aM1='a'-1;
      char zP1='z'+1;
      while((success==0)&&(cS>-1)){
          if((res[cS]>zeroM1)&&(res[cS]<'9')){
              res[cS]=res[cS]+1;success=1;
          }
          if((success==0)&&(res[cS]=='9')){
              res[cS]='a';success=1;
          }
          if((success==0)&&(res[cS]>aM1)&&(res[cS]<zP1)){
              if(res[cS]<'z'){
                  res[cS]=res[cS]+1;
                  success=1;
              }
              else{
                  res[cS]='0';
              }
          }
          cS--;
      }
      if(success==0){
          res='1'+res;
      }
      return res;
  }
}




#endif
