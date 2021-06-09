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


#ifndef _INCL_DISPLAYPREPARATIONS_CPP
#define _INCL_DISPLAYPREPARATIONS_CPP

namespace DISPPF{
  void dollarsToLatexSymbols(std::string & output,const long &singleDollarsAlso  =1){
    std::string scramble="#flkj!fjkl!!&#&#@*#*#@";

    std::vector<std::string> w2El;
    w2El.resize(2);
    output=SF::findAndReplace(output,"\\$",scramble);

    w2El[0]="\\[";w2El[1]="\\]";
    output=SF::findAndReplace(output,"$$",w2El);
    if(singleDollarsAlso==1){
      w2El[0]="\\(";w2El[1]="\\)";
      output=SF::findAndReplace(output,"$",w2El);
    }
    output=SF::findAndReplace(output,scramble,"\\$");
  }
  int removeBoxCodeToSafety(PTKF::PlainTextKeeper &kc, std::string &t,const std::string & s_B="_codeBox_",const std::string & s_E="_/codeBox_"){
    //returns 1 if everything is removed properly
    // returns 0 if there is an open tag or a tag inside a tag

    int correct=1;
    long pos;
    std::pair<std::string,int> allD;
    std::string ttd, dRec;
    pos=0;
    allD=SF::getNextString(t,pos,s_B,s_E);

    while(allD.second==1){


      ttd=s_B+allD.first+s_E;
      dRec=kc.depositTxt(ttd);
      t=SF::findAndReplace(t,ttd,dRec,0);
      pos=0;
      allD=SF::getNextString(t,pos,s_B,s_E);
    }


    return correct;
  }

  int removeToSafety(PTKF::PlainTextKeeper &kc, std::string &t,const std::string & s_B,const std::string & s_E){
    //returns 1 if everything is removed properly
    // returns 0 if there is an open tag or a tag inside a tag

    int correct=1;
    long pos;
    std::pair<std::string,int> allD;
    std::string ttd, dRec;
    pos=0;
    allD=SF::getNextString(t,pos,s_B,s_E);

    while(allD.second==1){
      if(correct==1){
        if(allD.first!=SF::findAndReplace(allD.first,s_B,"")) {
          correct=0;
        }
      }

      ttd=s_B+allD.first+s_E;
      dRec=kc.depositTxt(ttd);
      t=SF::findAndReplace(t,ttd,dRec,0);
      pos=0;
      allD=SF::getNextString(t,pos,s_B,s_E);
    }
    if(correct==1){
      if(t!=SF::findAndReplace(t,s_E,"")){
        correct=0;
      }
    }
    if(correct==1){
      if(t!=SF::findAndReplace(t,s_B,"")){
        correct=0;
      }
    }
    return correct;
  }

  class HTML_Tags{
  private:
    std::string scramble="#jkh!*K1&&&#";
  public:

    std::vector<std::string> formattingTags;
    std::vector<std::string> dangerousStrings;
    std::vector<std::string> scrambles;
    HTML_Tags();
  };
  HTML_Tags::HTML_Tags(){
    formattingTags.resize(21);

    formattingTags[0]="<i>";
    formattingTags[1]="</i>";
    formattingTags[2]="<b>";
    formattingTags[3]="</b>";
    formattingTags[4]="<u>";
    formattingTags[5]="</u>";
    formattingTags[6]="<ul>";
    formattingTags[7]="</ul>";
    formattingTags[8]="<li>";
    formattingTags[9]="</li>";
    formattingTags[10]="<p>";
    formattingTags[11]="</p>";
    formattingTags[12]="<title>";
    formattingTags[13]="</title>";
    formattingTags[14]="<h1>";
    formattingTags[15]="</h1>";
    formattingTags[16]="<h2>";
    formattingTags[17]="</h2>";
    formattingTags[18]="<h3>";
    formattingTags[19]="</h3>";
    formattingTags[20]="<br>";

    dangerousStrings.resize(2);

    dangerousStrings[0]="<?";
    dangerousStrings[1]="<php";

    long sz=formattingTags.size();
    scrambles.resize(sz);
    for(long i=0;i<sz;++i){
      scrambles[i]=scramble+std::to_string(i)+"e|";
    }

  }
  HTML_Tags GL_HTML_Tags;

  std::string treatHideReveal(const std::string & _input){
    std::string output=_input;
    long pos,posToSave;
    std::pair<std::string,int> allD;
    std::string revT,hideT,text,nt,oldText;
    long counter=0;std::string counterSt;
    pos=0;allD=SF::getNextString(output,pos,"_hideReveal_","_/hideReveal_");
    while(allD.second==1){
      text=allD.first;
      oldText="_hideReveal_"+text+"_/hideReveal_";
      posToSave=pos;
      posToSave-=text.size();
      if(posToSave<0){
        posToSave=0;
      }

      pos=0;allD=SF::getNextString(text,pos,"_hideTitle_","_/hideTitle_");
      hideT="Hide";
      if(allD.second==1){
        hideT=allD.first;
      }
      pos=0;allD=SF::replaceNextString(text,pos,"_hideTitle_","_/hideTitle_");
      if(allD.second==1){
        text=allD.first;
      }

      pos=0;allD=SF::getNextString(text,pos,"_revealTitle_","_/revealTitle_");
      revT="Show";
      if(allD.second==1){
        revT=allD.first;
      }
      pos=0;allD=SF::replaceNextString(text,pos,"_revealTitle_","_/revealTitle_");
      if(allD.second==1){
        text=allD.first;
      }
      counterSt=std::to_string(counter);
      nt="<div id=\"someText3"+counterSt+"\">\n";
      nt+="<a id=\"headerL3"+counterSt+"\" href=\"javascript:toggle(&#39;mCont3"+counterSt+"&#39;, ";
      nt+="&#39;hDiv3"+counterSt+"&#39;, &#39;"+revT+"&#39;, &#39;"+hideT+"&#39; ) ;\" ><span id=\"hDiv3";
      nt+=counterSt+"\">"+revT+"</span></a>\n";
      nt+="</div><div id=\"mCont3"+counterSt+"\" class=\"messageBox\" style=\"background-color:#e9ebf3; display: none;\">";
      nt+=text+"</div>";
      output=SF::findAndReplace(output,oldText,nt);

      pos=posToSave;
      pos=0;
      allD=SF::getNextString(output,pos,"_hideReveal_","_/hideReveal_");
      ++counter;
    }
    return output;
  }

  std::string formattingCommands(const std::string & _input){
    std::string output=_input;

    output=treatHideReveal(output);
    return output;

  }

  std::string sanitizeForDisplay(const std::string & _t,
                                 const long & convertDollarsToLatex=0,
                                 const long & htmlTolerance=0,
                                 const long & exitWithErrorIfUnsafe=1){
  //htmlTolerance:
  // 0 - no html codes. Outside of math and code blocks every < is replaced by \(<\)
  //     and every > is replaced by \(>\))

  // 1 - allow formatting tags.  WARNING -- not implemented yet

  // 2 - allow all tags except for dangerous ones

    PTKF::PlainTextKeeper keeperOfVerbatim("vb0b");

    PTKF::PlainTextKeeper keeperOfCodesB("sc0b");
    PTKF::PlainTextKeeper keeperOfBoxCodes("sc0bb");
    PTKF::PlainTextKeeper keeperOfCodesS("sc0s");

    std::string t=_t;

    std::string unsafe="Latex Error ";
    int indicatorSafety;

    indicatorSafety=removeToSafety(keeperOfVerbatim,t,"_verbatim_","_/verbatim_");
    if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
      return unsafe+" 1";
    }
    indicatorSafety=removeToSafety(keeperOfCodesB,t,"_code_","_/code_");
    if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
      return unsafe+" 2";
    }
    indicatorSafety=removeBoxCodeToSafety(keeperOfBoxCodes,t,"_codeBox_","_/codeBox_");
    if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
      return unsafe+" 4";
    }
    indicatorSafety=removeToSafety(keeperOfCodesS,t,"_cde_","_/cde_");
    if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
      return unsafe+" 3";
    }
    keeperOfVerbatim.treatCDE("_verbatim_","_/verbatim_");
    keeperOfCodesB.treatCODE();
    keeperOfCodesS.treatCDE();
    keeperOfBoxCodes.treatBoxCode();

    if(convertDollarsToLatex==1){
      std::vector<std::string>ws;
      ws.resize(2);
      ws[0]="1";ws[1]="2";
      dollarsToLatexSymbols(t);
    }

    long sz=GL_HTML_Tags.dangerousStrings.size();
    for(long i=0;i<sz;++i){
      t=SF::findAndReplace(t,GL_HTML_Tags.dangerousStrings[i],"");
    }




    if(htmlTolerance<2){
      PTKF::PlainTextKeeper mth1("m01");
      indicatorSafety=removeToSafety(mth1,t,"\\(","\\)");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+" 4 ";
      }
      PTKF::PlainTextKeeper mth2("m02");
      indicatorSafety=removeToSafety(mth2,t,"\\[","\\]");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+"5";
      }
      PTKF::PlainTextKeeper mth3("m03");
      indicatorSafety=removeToSafety(mth3,t,"\\begin{eqnarray*}","\\end{eqnarray*}");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+"6";
      }
      PTKF::PlainTextKeeper mth4("m04");
      indicatorSafety=removeToSafety(mth4,t,"\\begin{eqnarray}","\\end{eqnarray}");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+"7";
      }
      PTKF::PlainTextKeeper mth5("m05");
      indicatorSafety=removeToSafety(mth5,t,"\\begin{equation}","\\end{equation}");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+"8";
      }
      PTKF::PlainTextKeeper mth6("m06");
      indicatorSafety=removeToSafety(mth6,t,"\\begin{equation}","\\end{equation}");
      if((1-indicatorSafety)*exitWithErrorIfUnsafe==1){
        return unsafe+"9";
      }

      if(htmlTolerance==1){
        sz=GL_HTML_Tags.formattingTags.size();
        for(long i=0;i<sz;++i){
          t=SF::findAndReplace(t,GL_HTML_Tags.formattingTags[i],GL_HTML_Tags.scrambles[i]);
        }
      }
      t=SF::findAndReplace(t,"<","\\(<\\)");
      t=SF::findAndReplace(t,">","\\(>\\)");
      if(htmlTolerance==1){
        sz=GL_HTML_Tags.formattingTags.size();
        for(long i=0;i<sz;++i){
          t=SF::findAndReplace(t,GL_HTML_Tags.scrambles[i],GL_HTML_Tags.formattingTags[i]);
        }
      }

      t=mth6.recover(t);
      t=mth5.recover(t);
      t=mth4.recover(t);
      t=mth3.recover(t);
      t=mth2.recover(t);
      t=mth1.recover(t);

    }
    t=formattingCommands(t);
    t=keeperOfCodesS.recover(t);
    t=keeperOfCodesB.recover(t);
    t=keeperOfVerbatim.recover(t);
    t=keeperOfBoxCodes.recover(t);
    return t;

  }


  std::string finalizeForDisplay(const std::map<std::string,std::string> &findReplacePairs, const std::string & _t){
    std::string t=_t;
    std::map<std::string,std::string>::const_iterator itFR,itFRE;
    itFR=findReplacePairs.cbegin();
    itFRE=findReplacePairs.cend();
    while(itFR!=itFRE){
      t=SF::findAndReplace(t,itFR->first,itFR->second);
      ++itFR;
    }
    t=LNF::labelsAndNumbers(t);
    std::string fR= PTKF::GL_PLAINTEXT_KEEPER.recover(sanitizeForDisplay(t,1,2,0));
    fR=SF::massiveFiReplReverse(fR,HCBF::verySafePlace,0);
    return fR;
  }
  long checkForHTMLAwareness(const std::string &input){
    std::string out1;
    out1=SF::findAndReplace(input,"<br>","!",0,0);
    if(out1.length()!=input.length()){
      return 1;
    }
    out1=SF::findAndReplace(input,"<p>","!",0,0);
    if(out1.length()!=input.length()){
      return 1;
    }
    out1=SF::findAndReplace(input,"<div>","!",0,0);
    if(out1.length()!=input.length()){
      return 1;
    }
    out1=SF::findAndReplace(input,"<b>","!",0,0);
    if(out1.length()!=input.length()){
      return 1;
    }
    return 0;
  }
  std::string prepareForHTMLDisplay(const std::string &_st){

    std::string output=_st;
    output=SF::findAndReplace(output,"<<","!*c#o#u#t*!");
    output=SF::findAndReplace(output,">>","!*c#i#n*!");
    output=SF::findAndReplace(output,"<"," < ");
    output=SF::findAndReplace(output,">"," > ");
    output=SF::findAndReplace(output,"!*c#o#u#t*!","<<");
    output=SF::findAndReplace(output,"!*c#i#n*!",">>");


    output=sanitizeForDisplay(output,1);
    output=SF::findAndReplace(output,"\n","<BR>");
    return output;

  }
}
#endif
