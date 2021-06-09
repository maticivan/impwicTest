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


#ifndef _INCL_PlainTextKeeper_CPP
#define _INCL_PlainTextKeeper_CPP

namespace PTKF{
  class PlainTextKeeper{
  private:
    std::string sepBStB="_pTB*";
    std::string sepBStE="_/pTB*";
    std::string sepEC="!|!|_";

    std::string sepB;//="_pTB*!|!|_";
    std::string sepE;//="_/pTB*!|!|_";

    std::map<long,std::string> plainTextBank;
    std::string generateReceipt(const long & ) const;
  public:
    PlainTextKeeper(const std::string &);
    std::string depositTxt(const std::string &);
    std::string recover(const std::string &) const;

    void treatCODE(const std::string & ="_code_", const std::string & = "_/code_");
    void treatCDE(const std::string & ="_cde_", const std::string & = "_/cde_");
    void treatBoxCode();

  };

  void treatHTMLTagsInNonMathText(std::string &t){
    t=SF::findAndReplace(t,"<","\\(<\\)");
    t=SF::findAndReplace(t,">","\\(>\\)");
  }

  void makeItMoreProfessional(std::string & t){
    t=SF::findAndReplace(t,"\n","<BR>");
    std::vector<std::string> seqLongSpaces,seqQuads;
    std::string currentLongSpace="  ",currentQuad="\\quad";
    long numS=25;
    seqLongSpaces.resize(numS);seqQuads.resize(numS);
    for(long i=0;i<numS;++i){
      seqLongSpaces[i]=currentLongSpace;
      seqQuads[i]=currentQuad;
      currentLongSpace+=" ";
      if(i%2==1){
        currentQuad+="\\quad";
      }
    }
    long i=numS;
    while(i>0){
      --i;
      t=SF::findAndReplace(t,seqLongSpaces[i],"\\("+seqQuads[i]+"\\)");
    }
  }

  PlainTextKeeper::PlainTextKeeper(const std::string & salt){
    plainTextBank.clear();
    sepB=sepBStB+salt+sepEC;
    sepE=sepBStE+salt+sepEC;
  }
  std::string PlainTextKeeper::generateReceipt(const long & i) const{
    return sepB+std::to_string(i)+sepE;
  }
  std::string PlainTextKeeper::depositTxt(const std::string & _t){
    long i=plainTextBank.size();
    plainTextBank[i]=_t;
    return generateReceipt(i);
  }
  std::string PlainTextKeeper::recover(const std::string & _textWithDeposits) const{
    std::map<long,std::string>::const_iterator it,itE;
    std::string returnText=_textWithDeposits;
    it=plainTextBank.begin();
    itE=plainTextBank.end();
    while(it!=itE){
      returnText=SF::findAndReplace(returnText,generateReceipt(it->first),it->second,0);
      ++it;
    }
    return returnText;
  }

  void PlainTextKeeper::treatCDE(const std::string & cdeOpen, const std::string & cdeClose){
    long sz=plainTextBank.size();
    std::string st;
    for(long i=0;i<sz;++i){
      st=plainTextBank[i];
      treatHTMLTagsInNonMathText(st);

      st=SF::findAndReplace(st,cdeOpen,"<span style=\"font-family:Lucida Console, monospace\">");
      st=SF::findAndReplace(st,cdeClose,"</span>");

      plainTextBank[i]=st;
    }

  }
  void PlainTextKeeper::treatBoxCode(){

    long sz=plainTextBank.size();
    std::string st;
    std::pair<std::string,int> receiveRepl;
    // HCBF::verySafePlace vector of caracters will be used to hide all the tags that would be modified with other pieces of code
    // this will be returned in DISPPF::finalizeForDisplay()

    for(long i=0;i<sz;++i){
      receiveRepl=SF::replaceAllOuterLayerSeparators(plainTextBank[i],"_codeBox_", "_/codeBox_","<p><textarea class=\"form-control\" rows=\"10\">","</textarea></p>",HCBF::verySafePlace);
      if(receiveRepl.second==1){
        plainTextBank[i]=receiveRepl.first;
      }
    }
  }

  void PlainTextKeeper::treatCODE(const std::string & codeOpen, const std::string & codeClose){
    long sz=plainTextBank.size();
    std::string st,st1;
    long indicatorProfessionalUser;
    indicatorProfessionalUser=0;
    for(long i=0;i<sz;++i){
      indicatorProfessionalUser=0;

      st=plainTextBank[i];


      st1=SF::findAndReplace(st,"<BR>","");
      if(st1!=st){
        indicatorProfessionalUser=1;
      }
      else{
        st1=SF::findAndReplace(st,"<br>","");
        if(st1!=st){
          indicatorProfessionalUser=1;
        }
        else{
          st1=SF::findAndReplace(st,"\\quad","");
          if(st1!=st){
            indicatorProfessionalUser=1;
          }
        }
      }
      if(indicatorProfessionalUser==1){
        st=SF::findAndReplace(st,"<br>","_br_");
      }
      treatHTMLTagsInNonMathText(st);
      if(indicatorProfessionalUser==0){
        makeItMoreProfessional(st);
      }
      else{
        st=SF::findAndReplace(st,"$\\quad","\\(\\quad");
        st=SF::findAndReplace(st,"\\quad$","\\quad\\)");
        st=SF::findAndReplace(st,"_br_","<BR>");
        st=SF::findAndReplace(st,"_quot_","\"");
      }
      st=SF::findAndReplace(st,codeOpen,"<p style=\"font-family:Lucida Console, monospace\">");
      st=SF::findAndReplace(st,codeClose,"</p>");




      plainTextBank[i]=st;
    }

  }


  PlainTextKeeper GL_PLAINTEXT_KEEPER("gl0bal");
}


#endif
