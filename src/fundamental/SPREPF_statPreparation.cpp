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


#ifndef _INCL_STATPREPARATION_CPP
#define _INCL_STATPREPARATION_CPP

namespace SPREPF{
  struct StructStatConstants{
  public:
    long maxNumFiles=100;
    long maxItemsInFile=250;
    long paddingConst=100000;

    long numFilesToLookForSpammerBehavior=3;


    long numLoginAttemptsToStartCollectingData=5;

    long numLoginAttemptsToGetSuspcious=7;

    long cutoff_in_seconds_ForStalling=5;

    std::string sepStat_NRDB="_nD*_";
    std::string sepStat_NRDE="_/nD*_";
    std::string sepStat_akzDB="aaaDZMB";
    std::string sepStat_akzDE="aaaDZME";


      std::string sepStat_NRSB="_nS*_";
      std::string sepStat_NRSE="_/nS*_";
      std::string sepStat_akzSB="aaaSZMB";
      std::string sepStat_akzSE="aaaSZME";

  } STAT_CONSTS;

  struct StatData{
  public:
    std::string userName;
    std::string timeString;
    std::string att_page;
    std::string att_rr;
    std::string pass1;

    std::string putIntoString() const;
    void setFromString(const std::string &s);
  };
  std::string statPrepare(const std::string &i){
    std::string o=i;
    o=SF::findAndReplace(o,STAT_CONSTS.sepStat_NRSB,STAT_CONSTS.sepStat_akzSB);
    o=SF::findAndReplace(o,STAT_CONSTS.sepStat_NRSE,STAT_CONSTS.sepStat_akzSE);
    o=SF::findAndReplace(o,STAT_CONSTS.sepStat_NRDB,STAT_CONSTS.sepStat_akzDB);
    o=SF::findAndReplace(o,STAT_CONSTS.sepStat_NRDE,STAT_CONSTS.sepStat_akzDE);
    if(o.size()>30){
      std::string newO="";
      for(long i=0;i<30;++i){
        newO+=o[i];
      }
      newO+="...(to large)";
      o=newO;
    }
    return o;
  }
  std::string StatData::putIntoString() const{
    std::string fR="";
    std::string bS=STAT_CONSTS.sepStat_NRSB;std::string eS=STAT_CONSTS.sepStat_NRSE;
    fR+=bS+statPrepare(userName)+eS;
    fR+=bS+statPrepare(timeString)+eS;
    fR+=bS+statPrepare(att_page)+eS;
    fR+=bS+statPrepare(att_rr)+eS;

    return fR;
  }
  void StatData::setFromString(const std::string &i){
    std::vector<std::string> dv=SF::getItems(i,STAT_CONSTS.sepStat_NRSB,STAT_CONSTS.sepStat_NRSE);
    long sz=dv.size();
    if(sz>4){
      userName=dv[0];
      timeString=dv[1];
      att_page=dv[3];
      att_rr=dv[4];
    }
  }
}


#endif
