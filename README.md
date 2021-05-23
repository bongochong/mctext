**MCText**

A clone of Guy Rutenberg's Markov Chain Text Generator using the Boost C++ library.

The [latest binary file](https://github.com/bongochong/mctext/releases/download/0.2-1.75/mctext) was compiled against libboost 1.75 in an x86_64 environment, and depends on the `boost-program-options` (or `libboost-program-options`) package. It is suitable for any x86_64 GNU/Linux distribution with that package installed. There are older binary files in this repository as well, for those with different versions of boost (though they will all only work on x86_64 processors).

Usage: `mctext -w[number of words] -s[number of steps] [FILE]`  
Flags are optional.

To compile it yourself, download this repo, ensure that the boost development libraries and the g++ compiler are installed, cd into the directory, and do the following:  
`./configure` + any options you might want to include  
`make`  
Easy.

It's an interesting markov chain tool, and fun to play around with.

Original is here: https://www.guyrutenberg.com/2008/04/30/mctext-02-a-markov-chain-text-generator/ This repo exists in order to keep that nice little program accessible and open to future updates.
