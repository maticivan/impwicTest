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


#ifndef _INCL_RESNODEINSERTIONORSPLIT_CPP
#define _INCL_RESNODEINSERTIONORSPLIT_CPP



namespace RNISF{
  template<typename TTT> struct ResultInsSplit{
  public:
    int indicatorInsertOrSplitOrNothing; // 0: nothing; 1: insert; 2: split
    HBF::Node<TTT> resultOfInsert;
    std::pair<HBF::Node<TTT>,HBF::Node<TTT> > resultOfSplit;
    std::pair<long, long> countsSplit;
    TTT centralValue;
    HDPF::Pointer<HBF::Node<TTT> > pointerToOldLocationOfTheCentralValue;
    long positionInNodeOfTheCentralValue;
  };
}

#endif
