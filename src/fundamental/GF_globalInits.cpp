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


#ifndef _INCL_GF_GLOBALINITS_CPP
#define _INCL_GF_GLOBALINITS_CPP

namespace GF{
  DEBMF::DebHandler GL_DEB_MESSAGES;


  std::map<std::string,std::string> GL_OPENED_FILES;
  long GL_MAXFILESINRAM=1000;

  long GLOBAL_FILETOSTRCOUNTER=0;
  std::string GLOBAL_FILEOPENED;
  std::map<std::string,std::map<std::string,double> > initializeLetterGradesConversionMap(){
    std::map<std::string,std::map<std::string,double> > fR;
    std::map<std::string,double> aConv;
    aConv["A+"]=4.0;
    aConv["A"]=4.0;
    aConv["A-"]=3.7;
    aConv["B+"]=3.3;
    aConv["B"]=3.0;
    aConv["B-"]=2.7;
    aConv["C+"]=2.3;
    aConv["C"]=2.0;
    aConv["C-"]=1.7;
    aConv["D+"]=1.3;
    aConv["D"]=1.0;
    aConv["F"]=0.0;
    aConv["WU"]=0.0;
    fR["Baruch"]=aConv;
    return fR;
  }
  std::map<std::string,std::map<std::string,double> > GL_GRADE_CONVERSION=initializeLetterGradesConversionMap();

  long GL_randSeed= std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 GL_mt_randIF(GL_randSeed);
}


#endif
