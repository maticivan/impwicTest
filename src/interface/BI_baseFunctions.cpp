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


#ifndef _INCL_WI_BASICFUNCTIONS_CPP
#define _INCL_WI_BASICFUNCTIONS_CPP

namespace BI{
  const long GL_NUM_ENV=27;

  const std::string GL_ENV[ GL_NUM_ENV ] = {
     "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
     "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
     "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
     "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
     "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
     "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
     "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
     "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",
     "SERVER_SIGNATURE","SERVER_SOFTWARE", "HTTP_COOKIE", "CONTENT_TYPE", "CONTENT_LENGTH" };

  std::string envToHTML(const std::vector<std::string> &_e){
    std::string fR;
    fR="<TABLE BORDER = \"0\">";

    for(long i=0;i<GL_NUM_ENV;++i){
      fR+="<TR><TD>"+GL_ENV[i]+"</TD><TD>";
      fR+=_e[i];
      fR+="</TD></TR>\n";
    }
    fR+="</TABLE>\n";
    return fR;
  }

  std::vector<std::string> getEnvVars(){
    std::vector<std::string> fR;
    long numEnvVars=GL_NUM_ENV;
    fR.resize(numEnvVars);
    for(long i=0;i<numEnvVars;++i){
      char* value =  getenv(GL_ENV[ i ].c_str() ) ;

        if ( value  != nullptr ) {
           fR[i]=    value  ;
        } else {
           fR[i]= "notFound";
        }
    }
    return fR;
  }
  std::string textAreaField(const std::string & name="mText", const std::string & defaultT="", const long & numR=20, const long &numC=120){
    std::string fR="<textarea class=\"form-control\" name=\""+name+"\" rows=\""+std::to_string(numR);
    fR+="\"";
    //fR+="cols=\""+std::to_string(numC)+"\"";
    fR+=">";
    fR+=PTKF::GL_PLAINTEXT_KEEPER.depositTxt(defaultT)+"</textarea>\n";
    return fR;
  }

  std::string radioButtonsField(const std::string & name, const std::vector<std::string> & allChoicesValues, const std::vector<std::string> &allChoicesDescriptions,const std::string &preSelection){
    std::string fR="";
    long sz=allChoicesValues.size();
    fR+="<div class=\"card\">\n<div class=\"card-body\">";

    std::vector<std::string> bgColors;
    bgColors.resize(2);
    bgColors[0]="bg-light";
    bgColors[1]="";
    long bgCInd=0;
    for(long i=0;i<sz;++i){
      fR+="<div class=\"custom-control custom-radio\"><input type=\"radio\" ";
      fR+=" class=\"custom-control-input\" ";
      fR+="id=\""+name+allChoicesValues[i]+"\" ";
      fR+="name=\""+name;

      fR+="\" value=\""+allChoicesValues[i]+"\"";
      if (preSelection==allChoicesValues[i]){
        fR+=" checked=\"checked\"";
      }
      fR+=">  ";
      fR+=" <label class=\"custom-control-label\" for=\"" +name+allChoicesValues[i];
      fR+="\">";
      fR+=allChoicesDescriptions[i];
      fR+="</label>";
      fR+="</div>\n";
      ++bgCInd;bgCInd%=2;
    }
    fR+="</div>\n</div>\n";
    return fR;
  }

  std::string textInputField(const std::string & name="field01", const std::string & defaultT="", const long &sz = 30){
    std::string fR="<INPUT NAME=\""+name;
    fR+="\" VALUE=\"";
    std::string ty="password";
    if(defaultT!="password"){
      fR+=PTKF::GL_PLAINTEXT_KEEPER.depositTxt(defaultT);
      ty="text";
    }
    fR+="\" TYPE=\""+ty+"\" SIZE=\"";
    fR+=std::to_string(sz)+"\">";
    return fR;
  }
  std::string submButton(const std::string &aN,const std::string &bL){
    std::string fR;
    fR+="<button type=\"submit\" name=\""+aN+ "\" class=\"btn btn-primary mb-2\" VALUE=\"";
    fR+=bL;
    fR+= "\">";
    fR+=bL;fR+="</button>";
    return fR;
  }
  std::string setCookie(const std::string &cookieName="mc", const std::string &cookieValue="myFirstCookie"){
    std::string fR="";
    fR+="Set-Cookie:";
    fR+=cookieName;fR+="=";fR+=cookieValue;
    fR+=";";

    return fR;
  }
}

#endif
