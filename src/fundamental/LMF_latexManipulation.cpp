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


#ifndef _INCL_LATEXMANIPULATION_CPP
#define _INCL_LATEXMANIPULATION_CPP

namespace LMF{
  struct LatexDataSingleQuestion{
    std::string formulation;
    std::string questionType;
    std::string multipleChoicesSt;
    std::string pointsSt;
    long questionNumber;
    std::string solution;
    std::string answer;
  };

  struct LatexDataExamPaper{
    std::string studentName;
    std::string examCode;
    std::string studentCode;
    std::string courseName;
    std::string courseCode;
    std::string storageLocation;

    std::string examPreambleLatexTemplate;
    std::string answerBoxLatexTemplate;

    std::string prefix;
    std::string addNameIndicator;

    std::stack<LatexDataSingleQuestion> questionsStack;

  };



  long calculateWidth(const std::string & _input){
    std::string input=_input;
    std::string input2=input;
    input=SF::findAndReplace(input,"eqnarray","a");
    input=SF::findAndReplace(input,"$$","a");
    if(input.length()!=input2.length()){
      return 500;
    }

    input=SF::findAndReplace(input,"\\frac","");
    input=SF::findAndReplace(input,"\\hfill","");
    input=SF::findAndReplace(input,"\\mathbb","");
    input=SF::findAndReplace(input,"\\mathcal","");
    input=SF::findAndReplace(input,"\\noindent","");
    input=SF::findAndReplace(input,"\\alpha","a");
    input=SF::findAndReplace(input,"\\beta","a");
    input=SF::findAndReplace(input,"\\gamma","a");
    input=SF::findAndReplace(input,"\\delta","a");
    input=SF::findAndReplace(input,"\\varphi","a");
    input=SF::findAndReplace(input,"\\phi","a");
    input=SF::findAndReplace(input,"\\Phi","a");
    input=SF::findAndReplace(input,"\\Gamma","a");
    input=SF::findAndReplace(input,"\\nabla","a");
    input=SF::findAndReplace(input,"\\circ","a");
    input=SF::findAndReplace(input,"\\mapsto","a");
    input=SF::findAndReplace(input,"\\to","a");
    input=SF::findAndReplace(input,"\\left","a");
    input=SF::findAndReplace(input,"\\right","a");
    input=SF::findAndReplace(input,"\\equiv","a");
    input=SF::findAndReplace(input,"\\cong","a");
    input=SF::findAndReplace(input,"\\triangle","a");
    input=SF::findAndReplace(input,"\\star","a");
    input=SF::findAndReplace(input,"\\ast","a");




    return input.length();

  }

  long calculateProblemHeight(const std::string & _input){
    std::string input=_input;
    input=SF::findAndReplace(input,"\n","_nL*_s_/nL*_");
    input=SF::findAndReplace(input,"\\item","_nL*_s_/nL*_");
    input=SF::findAndReplace(input,"\\\\","_nL*_s_/nL*_");
    input=SF::findAndReplace(input,"\\begin{enumerate}","_nL*_s_/nL*_");
    input=SF::findAndReplace(input,"\\begin{itemize}","_nL*_s_/nL*_");

    long countNLines=SF::countInString(input,"_nL*_","_/nL*_");
    return countNLines + (input.length() / 150);
  }
  std::string prepareMultipleChoiceText(const std::string & mcst){
    long numCharactersToSwithToLines=120;
    std::string fRSpaces="", fRNLines="";
    std::string fRSpacesStart="\n\n \\vspace{0.3cm}\\ \\noindent ";
    std::string fRNLinesStart="\n\n \\vspace{0.3cm}\\ \\noindent ";
    std::vector<std::string> mcVect=SF::getItems(mcst,"_rb*_","_/rb*_");
    long vSize=mcVect.size();
    std::vector<std::string> vPair;
    long doneFirst=0;
    for(long i=0;i<vSize;++i){
      vPair=SF::getItems(mcVect[i],"_vl*_","_/vl*_");
      if(vPair[0]!="N"){
        if(doneFirst==1){
          fRSpaces+="\\hfill ";
          fRNLines+="\n\n \\noindent ";
        }
        if(vPair.size()>1){
          fRSpaces+=vPair[1]+" ";
          fRNLines+=vPair[1]+" ";
        }
      }
      doneFirst=1;
    }
    long wdth=calculateWidth(fRSpaces);
    if(wdth>numCharactersToSwithToLines){
      return fRNLinesStart+ fRNLines;
    }
    return fRSpacesStart+ fRSpaces;
  }
  std::string htmlToLatexPictures(const std::string & _input){
    std::string input=_input;
    long pos;
    std::pair<std::string,int> allD;
    pos=0;allD=SF::getNextString(input,pos,"<img ","\">");
    std::string fName,oldText;
    while(allD.second==1){

      fName=allD.first;
      oldText="<img "+fName+"\">";
      fName+="_/n*_ end";
      pos=0;allD=SF::getNextString(fName,pos,"src=\"","_/n*_");
      if(allD.second==1){
        fName=allD.first;
        fName=SF::findAndReplace(fName,".gif",".png");
        input=SF::findAndReplace(input,oldText,"\\includegraphics[scale=0.3]{."+fName+"}");
      }
      pos=0;allD=SF::getNextString(input,pos,"<img ","\">");
    }
    return input;
  }
  std::string htmlToLatexFormatting(const std::string &_input){
    std::string input=_input;
    input=SF::findAndReplace(input,"<b>","{\\bf ");
    input=SF::findAndReplace(input,"</b>","}");
    input=SF::findAndReplace(input,"<i>","{\\em ");
    input=SF::findAndReplace(input,"</i>","}");
    input=SF::findAndReplace(input,"_cde_","\\verb@");
    input=SF::findAndReplace(input,"_/cde_","@");
    input=SF::findAndReplace(input,"_code_","\\begin{verbatim}");
    input=SF::findAndReplace(input,"_/code_","\\end{verbatim}");
    input=SF::findAndReplace(input,"\\newline","\\\\");
    input=SF::findAndReplace(input,"<ul>","\\begin{itemize}");
    input=SF::findAndReplace(input,"</ul>","\\end{itemize}");
    input=SF::findAndReplace(input,"<center>","\\begin{center}");
    input=SF::findAndReplace(input,"</center>","\\end{center}");
    input=SF::findAndReplace(input,"<li>","\\item");
    input=SF::findAndReplace(input,"</li>","");
    input=SF::findAndReplace(input,"<br>","\n\n");
    input=SF::findAndReplace(input,"<p>","\n\n");
    input=SF::findAndReplace(input,"<div>","\n\n");
    input=SF::findAndReplace(input,"</p>","");
    input=SF::findAndReplace(input,"</div>","");
    input=SF::findAndReplace(input,"</br>","");


    input=htmlToLatexPictures(input);



    return input;

  }

  std::string prepareSingleProblemForPrinting(const LatexDataSingleQuestion & sq,const LatexDataExamPaper & exam){
    std::string fR="";
    fR+="\\item["+std::to_string(sq.questionNumber +1)+"] ";
    fR+="{\\bf ("+sq.pointsSt+" points)}";
    fR+=sq.formulation;
    if(sq.questionType=="radioButtonsField"){
      fR+=prepareMultipleChoiceText(sq.multipleChoicesSt);
    }
    if(sq.questionType=="textInputField"){
      fR+=exam.answerBoxLatexTemplate;
    }

    fR=htmlToLatexFormatting(fR);
    return fR;
  }

  std::string prepareLatexSource(const LatexDataExamPaper & exam){
    std::string fR="";

    long maxHeightForPage=25;

    std::string problemBreakString="\n\n\\vfill\n\n";
    std::string pageBreakString=problemBreakString+ "\\pagebreak\n";
    std::stack problems=exam.questionsStack;
    SF::flipTheStack(problems);
    std::string singleProblem;long pHeight;
    long currentHeight=0;
    while(!problems.empty()){

      singleProblem=prepareSingleProblemForPrinting(problems.top(),exam);
      pHeight=calculateProblemHeight(singleProblem);

      if(currentHeight>0){
        if(currentHeight+pHeight>maxHeightForPage){
          fR+=pageBreakString;
          currentHeight=pHeight;
        }
        else{
          currentHeight+=pHeight;
        }
      }
      else{
        currentHeight=pHeight;
      }

      fR+=singleProblem;
      fR+=problemBreakString;
 
      problems.pop();


    }

    fR= "\\begin{enumerate}\n"+ fR+"\\end{enumerate}\n";
    fR= "\\noindent {\\bf "+exam.studentName+"}\n\n"+fR;
    fR="\n\n \\begin{document}"+fR+"\n\n\\end{document} \n";
    fR=exam.examPreambleLatexTemplate+fR;
    return fR;
  }
  std::string prepareExamForPrinting(const LatexDataExamPaper & exam){
    std::string lSource=prepareLatexSource(exam);

    std::string lFName=exam.storageLocation+"/"+exam.prefix+exam.examCode;
    if(exam.addNameIndicator=="yes"){
      lFName+="_"+BF::cleanAllSpaces(exam.studentName);

    }

    IOF::toFile(lFName+".tex",lSource);

    std::string latexCommand="pdflatex -interaction=batchmode -output-directory="+exam.storageLocation;
    latexCommand+=" "+lFName+".tex";
    IOF::sys_runLatexCommand(latexCommand);
    IOF::sys_deleteFile(lFName+".out");
    IOF::sys_deleteFile(lFName+".log");
    IOF::sys_deleteFile(lFName+".aux");
    IOF::sys_deleteFile(lFName+".dvi");
    IOF::sys_deleteFile(lFName+".tex");
    return lFName+".pdf";
  }
}

#endif
