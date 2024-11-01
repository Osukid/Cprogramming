#include<stdio.h>
#include<windows.h>
/* init() will do the basic setting 
 It is void so it won't return anything 
 It doesn't get any params so for setting change here!
 
 x , y , board[][] get set as static:
 x , y define the board size
 board array is responisble of current game's status 
	and is defualted to all 0's in beginning
	user1 is shown by 1's 
	user2 is shown by 2's
	
	board is considered to have computer coordination
	meaning the top left is (0,0)
	
	the first row of board is not considered in the game
	it holdes a record of 'y' of the last empty hole
	if no more disc were allowed it will have -1
*/
	static int x = 7 , y = 7 , allowed = y;  // The defualt of 4-in-a-line is 7 * 6 circles 
	static int board[7][7]; 
void init(){
	
	// Setting every element of board to 0 except the first row:
	int i , j;
	for(i=1; i < x ; i++)
		for(j=0; j < y ; j++)
			board[i][j] = 0;
			
	// Setting every elemnt of the first row to the last row position:
	for(j=0; j < y ; j++)
			board[0][j] = 6;
}

/* drawer() will display the game's current status
*/
void drawer(){
	system("cls"); //erasing the previous console
	int i , j;
	for(i=1; i < x ; i++){
		for(j=0; j < y ; j++)
			printf("%d " , board[i][j]);
		printf("\n");
	}
	printf("\n-------------\n");	
}

/* user_input() is responsible of getting the column number from the user
	$user determines which player's turn it is which is 1 or 2
	it's only used in showing the text!
*/
int user_input(int user){
	int user_value;
	printf("user%d's turn!\nPlease enter the number of column you want to drop your disc to: " , user);
	scanf("%d" , &user_value);
	user_value--; // the array is 0-based!
	
	// If the input was not valid
	if(user_value > 6 || user_value < 0){
		drawer(); // drawing the page again
		printf("Please Enter a valid number!\n");
		user_value = user_input(user);
	}
	
	return user_value;
}

/* gamer() will set the board according to what the user said
	it gets a user_value which is the column the user wanted 0-based
	and a user which is 1 or 2
*/
void gamer(int user_value , int user){
			if(board[0][user_value] != -1){
				if(board[0][user_value] > 1){
					board[board[0][user_value]][user_value] = user;
					board[0][user_value]--;
				}
				else{
					board[board[0][user_value]][user_value] = user;
					board[0][user_value] = -1;
					allowed--;h
				}
			}
			else{
				drawer(); // drawing the page again
				printf("This column is full! Try another one!\n");
				gamer(user_input(user) , user);
			}
}

/* InLine(px , py) is the judge!
	it checks if the condition of 4-in-a-line is true or not
	in the case it was it returns 1 
	else 0
	
	when 1 was returned the game should be over!
*/
int InLine(int px , int py){
	int val = board[px][py];
	
	if(val == 0) // the element is empty
		return 0;
		
	// if the right side is valid:
	if(py + 3 < y){ 
		//checking the right
		if(board[px][py+1] == val && board[px][py+2] == val && board[px][py+3] == val)
			return 1;	
		//checking the upper right
		if(px - 3 >= 0 && board[px-1][py+1] == val && board[px-2][py+2] == val && board[px-3][py+3] == val)
			return 1;
		//checking the lower right		
		if(px + 3 <= 6 && board[px+1][py+1] == val && board[px+2][py+2] == val && board[px+3][py+3] == val)
			return 1;
	}
	
	// if the left side is valid:
	if(py - 3 >= 0){ 
		//checking the left
		if(board[px][py-1] == val && board[px][py-2] == val && board[px][py-3] == val)
			return 1;
		//checking the upper left
		if(py - 3 >= 0 && board[px-1][py-1] == val && board[px-2][py-2] == val && board[px-3][py-3] == val)
			return 1;
		//checking the lower left
		if(py + 3 <= 6 && board[px+1][py-1] == val && board[px+2][py-2] == val && board[px+3][py-3] == val)
			return 1;
	}
	
	//checking the down
	if(px + 3 <= 6 && board[px+1][py] == val && board[px+2][py] == val && board[px+3][py] == val)
		return 1;
	
	return 0; //none of above!
}
/* end() is the announcer of the result
	at the the end of the game.
	it gets a parameter c and 
	will print the appropriate statement
	
*/
void end(int c){
	drawer();
	switch (c) {
		case 0: // no more moves allowed! no user winned! equal!
			printf("WoW!\nYou two are both great masters!\nI should now announce that this game has reached a draw!");
			break;
		case 1: // user1 won!
			printf("And now...\nThe champion of the game...\nuser1 won!!!");
			break;
		case 2: // user2 won!
			printf("And now...\nThe champion of the game...\nuser2 won!!!");
			break;
	}
}

int main(){
	init();
	int turn = 1 , user_value = 0, result = 0 ; 
	/* user_value will be the value that user will enter each time
		result will have the ending result of the match and 
		is used in the end() function
	*/
	
	/* Errors:
		inLine not working
	*/
	
	while(1==1){
		drawer();
		// No more moves available!
		if(allowed == 0){
			result = 0;
			break;
		}
		// user1's turn!
		if(turn == 1){ 
			user_value = user_input(1);
			gamer(user_value , 1);
		}
		// user2's turn!
		else{ 
			user_value = user_input(2);
			gamer(user_value , 2);
		}
		// Checking if the new disc won the game
		if(InLine(board[0][user_value] + 1 , user_value) == 1){
			result = turn;
			break;
		}
		// Setting the next turn
		if(turn == 1)
			turn = 2;
		else
			turn = 1;
	}
	end(result);
	return 0;
}