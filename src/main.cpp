#include <getopt.h>
#include "ndtreehelper.h"

struct option longopts[] = {
    { "dimension", required_argument, NULL,'m'},
    { "index", required_argument, NULL,'i'},
    { "data", required_argument, NULL,'d'},
    { "boxquery", required_argument, NULL,'b'},
    { "querydim", required_argument, NULL,'q'},
    { "rangequery", required_argument, NULL,'r'},
    { "skip", required_argument, NULL,'s'},
    { "aux", required_argument, NULL,'a'},
    { "record", required_argument, NULL,'c'},
    { "newtree", no_argument, NULL,'n'},
    { "help", no_argument, NULL,'h'},
   {     0,    0,    0,    0},
};

//enum Action = {};

int main(int argc, char *argv[])
{
	ndtreeHelper ndtree;
	int query_dim = DIM;
	bool newTree = false;
	int c;
    	while((c = getopt_long(argc, argv, 
		"m:i:d:b:r:s:a:c:nh", longopts, NULL)) != -1){

		switch (c){
		case 'm':
		    printf("dimension is: %s\n", optarg);
		    break;
		case 'i':
		    printf("index file name is: %s\n", optarg);
		    globalIndexFilename = optarg;
		    break;
		case 'd':
		    printf("data file name is %s.\n", optarg);
		    globalDataFilename = optarg;
		    break;
		case 'b':
		    printf("box query file name is %s.\n", optarg);
		    globalBQFilename = optarg;
		    break;
		case 'q':
		    printf("query dimension is %s.\n", optarg);
		    query_dim = atoi(optarg);
		case 'r':
		    printf("range query file name is %s.\n", optarg);
		    globalRQFilename = optarg;
		    break;
		case 's':
		    printf("skip is %s.\n", optarg);
		    break;
		case 'a':
		    printf("aux file name is %s.\n", optarg);
		    globalAuxFilename = optarg;
		    break;
		case 'c':
		    printf("record file name is %s.\n", optarg);
		    globalRecordFilename = optarg;
		    break;
		case 'n':
		    printf("\ncreate new tree \n");
		    newTree = true;
		    break;
		case 'h':
		    printf("\nHelp information \n");
		    break;
		}
	}


        if(newTree)
        {
            cout<<"Creating a new index file"<<endl;
	    //original method, without link to data record
	    //batchBuild_with_duplicate(opt.count);
            ndtree.batchBuild_with_duplicate_record(LONG_MAX);
        }
        else
        {
            cout<<"Modifying an existing index file "<<endl;
	    //figure it out later
	    int skip = 10;
            ndtree.batchGrow_with_duplicate(skip, LONG_MAX);
        }
        cout<<"Box query file "<<globalBQFilename<<endl;
        
	if(query_dim > DIM) {
		cout << "big k search small k";
	} else if(query_dim < DIM) {
		cout << "small k search big k";
	}
	
	ndtree.batchRandomBoxQuery(query_dim);
    
}
