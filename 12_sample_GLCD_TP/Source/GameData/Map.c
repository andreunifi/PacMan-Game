


#include "GameData/Map.h"
#include <string.h>



int count=260;
int emptysize=0;

void initialize(int height, int width, 
                int emptytiles[height * width], 
                int wallstiles[height * width],
                int cointiles[height * width],
                int poweruptiles[height * width],
                char map[height][width]) {
								memset(wallstiles, 0, sizeof(int) * height * width);
									
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x; // Linear index for the 1D arrays

            if (map[y][x] == '#') { // Wall tiles
                emptytiles[index] = 0;
                wallstiles[index] = 1;
            } else { // Empty tiles
							if(map[y][x] == 'x') //out of bounds tiles, go away
								continue;
							
                emptytiles[index] = 1;
                wallstiles[index] = 0;
								emptysize++;
								map[y][x]=' ';
								if(count > 0 && !(y == 9 && (x == 0 || x == 29)) ){
									 //int value = rand() % (1 + 1);
									//if(value){
									map[y][x]='*';
									count--;
									
									//}
									
								}
									
            }

            if (map[y][x] == '*') { // Coin tiles
                cointiles[index] = 1;
            } else {
                cointiles[index] = 0;
            }

            if (y == 9 && (x == 29 || x == 0))
							teleportlocation[index]=1;
						
						
						
        }
    }
		map[1][1]='P';
		map[9][2]='O';
		count=240;
}




// Define the characters for the map
volatile char map[MAP_HEIGHT][MAP_WIDTH] = {
	
"##############################",
"#             ##             #",
"# ##### ##### ## ##### ##### #",
"# ##### #####    ##### ##### #",
"#                            #",
"#####  ##  ########  ##  #####",
"xxxx#  ###    ##    ###  #xxxx",
"xxxx#  ###    ##    ###  #xxxx",
"#####  ##     ##     ##  #####",
"<                            >",
"#####  ##  ###  ###  ##  #####",
"xxxx#  ##  #      #  ##  #xxxx",
"#####  ##  #      #  ##  #####",
"#      ##  #      #  ##      #",
"###  ####  ########  ####  ###",
"#    ####            ####    #",
"#                            #",                       	
"##############################",

	
	/*
    "##############################",
    "#P                           #",
    "#  #######  #######  ######  #",
    "#  #     #  #     #  #    #  #",
    "#  #     #  #     #  #    #  #",
    "#  #######  #     #  ######  #",
    "#                            #",
    "#  #######   #####   ######  #",
    "<                            >",        //9,
    "#  #######  #######  ######  #",
    "#  #     #  #     #  #    #  #",
    "#  #     #  #     #  #    #  #",
    "#  #######  #######  ######  #",
    "#                            #",
    "#  #######  #######  ######  #",
    "#  #     #  #     #  #    #  #",
    "#  #     #  #     #  #    #  #",
    "#  #######  #     #  ######  #",
    "#                            #",
    "##############################",
		
		*/
    
};

/*
##############################
#             ##             #
# ##### ##### ## ##### ##### #
# ##### #####    ##### ##### #
#                            #
#####  ##  ########  ##  #####
    #  ###    ##    ###  #
    #  ###    ##    ###  # 
#####  ##     ##     ##  #####
<					                   >
#####  #   ###  ###   #  #####    
		#  #   #      #   #  #		
#####  #   #      #   #  ##### 
#      #   #      #   #      # 
###  ### 	 ########   ###  ###
#                            #
##############################

*/