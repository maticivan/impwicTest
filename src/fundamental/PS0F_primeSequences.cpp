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

#ifndef _INCL_PrimeSequences_CPP
#define _INCL_PrimeSequences_CPP
namespace PS0F{
  class PrimeSequences{
  public:
    std::vector<long> primes;
    std::vector<long> mults;
    std::vector<long> inverses;
    std::vector<long> shifts;
    long paddingNumB;
    PrimeSequences();
  };
  PrimeSequences::PrimeSequences(){
    long sz=20;
    primes.resize(sz);
    mults.resize(sz);
    inverses.resize(sz);
    shifts.resize(sz);
    paddingNumB=1000000000000000;
    primes[0]=23894957;
    mults[0]=23771347;
    inverses[0]=13265461;
    shifts[0]=11955638;
    primes[1]=23895329;
    mults[1]=23771879;
    inverses[1]=17240446;
    shifts[1]=11956038;
    primes[2]=23896231;
    mults[2]=23772733;
    inverses[2]=18848530;
    shifts[2]=11956094;
    primes[3]=23897033;
    mults[3]=23773523;
    inverses[3]=8234038;
    shifts[3]=11956155;
    primes[4]=23897147;
    mults[4]=23773643;
    inverses[4]=3201727;
    shifts[4]=11956313;
    primes[5]=23897327;
    mults[5]=23773787;
    inverses[5]=12179435;
    shifts[5]=11956548;
    primes[6]=23897639;
    mults[6]=23774159;
    inverses[6]=1927410;
    shifts[6]=11956740;
    primes[7]=23898113;
    mults[7]=23774549;
    inverses[7]=15699407;
    shifts[7]=11957174;
    primes[8]=23898517;
    mults[8]=23774953;
    inverses[8]=8580636;
    shifts[8]=11957568;
    primes[9]=23899493;
    mults[9]=23775907;
    inverses[9]=19811946;
    shifts[9]=11957622;
    primes[10]=23900231;
    mults[10]=23776717;
    inverses[10]=11027497;
    shifts[10]=11957682;
    primes[11]=23900353;
    mults[11]=23776793;
    inverses[11]=11377040;
    shifts[11]=11957867;
    primes[12]=23900579;
    mults[12]=23776967;
    inverses[12]=2013757;
    shifts[12]=11958074;
    primes[13]=23900983;
    mults[13]=23777357;
    inverses[13]=16967869;
    shifts[13]=11958380;
    primes[14]=23901533;
    mults[14]=23777921;
    inverses[14]=1170404;
    shifts[14]=11958828;
    primes[15]=23901877;
    mults[15]=23778281;
    inverses[15]=13167537;
    shifts[15]=11959242;
    primes[16]=23902733;
    mults[16]=23779153;
    inverses[16]=19956403;
    shifts[16]=11959268;
    primes[17]=23903447;
    mults[17]=23779757;
    inverses[17]=590001;
    shifts[17]=11959377;
    primes[18]=23903549;
    mults[18]=23779859;
    inverses[18]=6951142;
    shifts[18]=11959572;
    primes[19]=23903749;
    mults[19]=23780063;
    inverses[19]=17185784;
    shifts[19]=11959823;
  }
}


#endif
