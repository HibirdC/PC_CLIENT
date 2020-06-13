#!/usr/bin/python3

#exec python getdbkey.py  [userId]
import sys 
import hashlib

arglen = len(sys.argv);

if arglen < 2:
	print("python enc.py <userId>");
	sys.exit();
#else:
#	print sys.argv;

if sys.argv[1].isdigit() :
	userId = int(sys.argv[1]);
	encode = "syswin_"+str(userId *8);
else :
	encode = "syswin";

md5 = hashlib.md5(encode).hexdigest();

print md5.upper();

