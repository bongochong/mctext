/***************************************************************************
 *   Copyright (C) 2008 by Guy Rutenberg                                   *
 *   guyrutenberg@gmail.com                                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <exception>
#include <iostream>
#include <boost/random/uniform_int.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/variate_generator.hpp>
#include <limits>

#include "text_generator.h"

using namespace std;

/**
 *\param sample_file an open stream to a file holding sample text.
 */
DefaultTextGenerator::DefaultTextGenerator()
{
	//TODO initialize the random number generator here;
}

/**
 * This function takes a string of words, and adds them into the sample text
 * base
 */
void DefaultTextGenerator::addWords(const std::string &str)
{
	string buf;
	stringstream ss(str);

	while (ss >> buf)
		m_words.push_back(buf);
	
}


string DefaultTextGenerator::generateWords(int count, const int steps)
{
	const int vec_length = m_words.size();
	if (vec_length < steps) {
		runtime_error e("Sample text too short");
		throw e;
	}

	string output;
	vector<string> temp;
	
	//TODO move the random number generator from here to a class member
	boost::uniform_int<size_t> uni_dist(0, vec_length-steps);
	boost::variate_generator<boost::rand48, boost::uniform_int<size_t> >
		rand(boost::rand48((int) time(NULL)), uni_dist);

	//this is for randomizing the search order
	boost::uniform_int<size_t> uni_int(0, std::numeric_limits<int>::max());
	boost::variate_generator<boost::rand48, boost::uniform_int<size_t> >
		randint(boost::rand48((int) time(NULL)), uni_int);
	//TODO check if we can give up on one of the random number generators
	
	int initial_rand = rand();
	for (int i=0; i<steps && count>0; ++i) {
		temp.push_back(m_words[initial_rand+i]);	
		--count;
	}
	vector< vector<string>::iterator > itr_vec; //this will hold iterator to results

	for (int i = count; i>0 ; --i) {
		itr_vec.clear();
		vector<string>::iterator last_it = m_words.begin();

		last_it = search(last_it, m_words.end()-1, temp.end()-steps, temp.end());

		while (last_it != (m_words.end()-1)) {
			itr_vec.push_back(last_it+steps);
			last_it = search(last_it+1, m_words.end()-1, temp.end()-steps, temp.end());
		}
		if (itr_vec.size()==0) { 
			//cerr<<"debug: don't know how to continue - "<<temp.size()<<endl;
			initial_rand = rand();
			for (int j=0; j<steps && i>0; ++j) {
				temp.push_back(m_words[initial_rand+j]);	
				--i;
			}
			continue;
		}
		temp.push_back( *(itr_vec[ randint()%itr_vec.size() ] ) ); //there is probably better way to code this
	}
	
	for (int i = 0; i < temp.size(); ++i) {
		output += temp[i]+" ";
	}
	return output;
}
