/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. */
#include <locale.h>
#include <string>
#include <iostream>
#include "io.h"
#include "filelist.h"
#include "inputhandle.h"
#include "../config.h"

using namespace std;


int main(int argc, char* argv[])
{
		setlocale(LC_ALL, "");
		string dirstr;
		if(argc < 2) // if no command line argument, read dir from stdin
				cin >> dirstr;
		else
		{
				if((dirstr = argv[1]) == "--help" || dirstr == "-h"
					|| dirstr == "-v" || dirstr == "--version")
				{
						cout << PACKAGE_STRING << endl <<
							"Please read the man page or the README file for instructions."
							<< endl;
						return 0;
				}
		}
		cout << "Reading directory and tags..." << endl;
		if(!get_directory(dirstr.c_str()))
				return 1;

		try {
			init_curses();
			for(vector<FilelistEntry>::const_iterator i = files.begin(); i != files.end(); ++i)
			{
				if(i->tags.unsaved_changes)
				{
					stat_msg("NOTE: some file names were autofixed!");
					break;
				}
			}
			mainloop();
		}
		catch(int e) // currently only too small screen throws
		{
				deinit_curses();
				cerr << endl << "Terminal size is too small, aborting! (" <<
					"needed at least " << MIN_COLS << 'x' << MIN_ROWS << ')' << endl;
				return -1;
		}

		deinit_curses();
		return 0;
}
