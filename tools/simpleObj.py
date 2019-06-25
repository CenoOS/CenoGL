

with open("../bunny.obj") as file:
	fo = open("../bunny_n.obj", "w")
	for line in file:
		vec = line.split( )
		if vec[0]=='v':
			fo.write(line);
		if vec[0]=='f':
			fo.write('f '+vec[1].split('/')[0]+' '+vec[2].split('/')[0]+' '+vec[3].split('/')[0]+'\n');