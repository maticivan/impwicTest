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

#ifndef _INCL_PermutationSequences_CPP
#define _INCL_PermutationSequences_CPP

namespace PS1F{
  class PermutationSequences{
  public:
    long lenEach=8;

    std::vector<std::vector<long> > indicatorCombinations;
    std::vector<std::vector< std::vector<long> > > pairsPermutations;
    PermutationSequences();
  };
  PermutationSequences::PermutationSequences(){
    long sz=3;
    indicatorCombinations.resize(sz);
    pairsPermutations.resize(sz);
    std::vector<std::vector<long> > onePairPermutations;
    onePairPermutations.resize(2);
    onePairPermutations[0].resize(lenEach);
    onePairPermutations[1].resize(lenEach);
    long lenEach2=2*lenEach;
    for(long i=0;i<sz;++i){
      indicatorCombinations[i].resize(lenEach2);
    }
    indicatorCombinations[0][0]=0;
    indicatorCombinations[0][1]=0;
    indicatorCombinations[0][2]=1;
    indicatorCombinations[0][3]=0;
    indicatorCombinations[0][4]=0;
    indicatorCombinations[0][5]=0;
    indicatorCombinations[0][6]=0;
    indicatorCombinations[0][7]=1;
    indicatorCombinations[0][8]=0;
    indicatorCombinations[0][9]=1;
    indicatorCombinations[0][10]=1;
    indicatorCombinations[0][11]=0;
    indicatorCombinations[0][12]=1;
    indicatorCombinations[0][13]=1;
    indicatorCombinations[0][14]=1;
    indicatorCombinations[0][15]=1;
    onePairPermutations[0][0]=4;
    onePairPermutations[0][1]=0;
    onePairPermutations[0][2]=7;
    onePairPermutations[0][3]=2;
    onePairPermutations[0][4]=3;
    onePairPermutations[0][5]=6;
    onePairPermutations[0][6]=5;
    onePairPermutations[0][7]=1;
    onePairPermutations[1][0]=7;
    onePairPermutations[1][1]=3;
    onePairPermutations[1][2]=4;
    onePairPermutations[1][3]=6;
    onePairPermutations[1][4]=1;
    onePairPermutations[1][5]=5;
    onePairPermutations[1][6]=0;
    onePairPermutations[1][7]=2;
    pairsPermutations[0]=onePairPermutations;
    indicatorCombinations[1][0]=1;
    indicatorCombinations[1][1]=0;
    indicatorCombinations[1][2]=0;
    indicatorCombinations[1][3]=1;
    indicatorCombinations[1][4]=1;
    indicatorCombinations[1][5]=1;
    indicatorCombinations[1][6]=0;
    indicatorCombinations[1][7]=0;
    indicatorCombinations[1][8]=1;
    indicatorCombinations[1][9]=0;
    indicatorCombinations[1][10]=1;
    indicatorCombinations[1][11]=0;
    indicatorCombinations[1][12]=1;
    indicatorCombinations[1][13]=0;
    indicatorCombinations[1][14]=1;
    indicatorCombinations[1][15]=0;
    onePairPermutations[0][0]=3;
    onePairPermutations[0][1]=5;
    onePairPermutations[0][2]=6;
    onePairPermutations[0][3]=7;
    onePairPermutations[0][4]=1;
    onePairPermutations[0][5]=0;
    onePairPermutations[0][6]=2;
    onePairPermutations[0][7]=4;
    onePairPermutations[1][0]=1;
    onePairPermutations[1][1]=2;
    onePairPermutations[1][2]=4;
    onePairPermutations[1][3]=3;
    onePairPermutations[1][4]=7;
    onePairPermutations[1][5]=6;
    onePairPermutations[1][6]=5;
    onePairPermutations[1][7]=0;
    pairsPermutations[1]=onePairPermutations;
    indicatorCombinations[2][0]=1;
    indicatorCombinations[2][1]=0;
    indicatorCombinations[2][2]=0;
    indicatorCombinations[2][3]=0;
    indicatorCombinations[2][4]=1;
    indicatorCombinations[2][5]=1;
    indicatorCombinations[2][6]=0;
    indicatorCombinations[2][7]=0;
    indicatorCombinations[2][8]=1;
    indicatorCombinations[2][9]=0;
    indicatorCombinations[2][10]=1;
    indicatorCombinations[2][11]=1;
    indicatorCombinations[2][12]=1;
    indicatorCombinations[2][13]=1;
    indicatorCombinations[2][14]=0;
    indicatorCombinations[2][15]=0;
    onePairPermutations[0][0]=2;
    onePairPermutations[0][1]=3;
    onePairPermutations[0][2]=5;
    onePairPermutations[0][3]=1;
    onePairPermutations[0][4]=4;
    onePairPermutations[0][5]=7;
    onePairPermutations[0][6]=0;
    onePairPermutations[0][7]=6;
    onePairPermutations[1][0]=1;
    onePairPermutations[1][1]=2;
    onePairPermutations[1][2]=3;
    onePairPermutations[1][3]=5;
    onePairPermutations[1][4]=4;
    onePairPermutations[1][5]=6;
    onePairPermutations[1][6]=0;
    onePairPermutations[1][7]=7;
    pairsPermutations[2]=onePairPermutations; 
  };
}

#endif
