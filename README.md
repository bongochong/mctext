**MCText**

A clone of Guy Rutenberg's Markov Chain Text Generator using the Boost C++ library.

The [binary file](https://github.com/bongochong/mctext-0.2/raw/master/binary/mctext) was compiled against libboost 1.67, and depends on the libboost-program-options package. It is suitable for any LiGNUx environment with that package installed.

Usage: `mctext -w[number of words] -s[number of steps] [FILE]`  
Flags are optional and text can be piped into it instead of a file.

It's an interesting markov chain tool, and fun to play around with.

Original is here: https://www.guyrutenberg.com/2008/04/30/mctext-02-a-markov-chain-text-generator/ This repo exists in order to keep that nice little program accessible and open to future updates.
