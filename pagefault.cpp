//This is the code for Lab 5 in CS3080
//Author: Austin Carico
//November 22nd, 2021
//This program finds the minimum number of page faults between LRU and FIFO

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>

  
#define NUM_REF 42 // Number of references
#define FRAME_START 3
#define FRAME_END   7


int FIFOMin  = 1000;
int LRUMin = 1000;
int frameMinFIFO = 1000;
int frameMinLRU = 1000;
int ref[NUM_REF] = {1, 2, 7, 4, 5, 2, 7, 2, 3, 2, 1, 7, 6, 3, 7, 6, 3, 
4, 3, 4, 3, 4, 7, 2, 1, 7, 6, 
7, 8, 7, 8, 9, 7, 8, 2, 7, 8, 
3, 5, 3, 5, 7 };


int ram_frames[FRAME_END];

void FIFO_Sim();    //FIFO Function Protocol
void LRU_Sim();
void Print_Results();


using namespace std;

int main()
{	
	//Declare Local Variable
	
	cout << endl;
	cout << "\n\n*** Virtual Memory Sim Program ***" << endl;
	
	FIFO_Sim(); // Algorithm Function Declarations
	LRU_Sim(); 
	Print_Results(); // Function to print minimum page faults


	cout << "\nEnd of Simulation" << endl;
	return 0;
	

}
void FIFO_Sim()
{
	int i, j, framecount;
	int page_fault;
	
	int found = 0; // Declare variable to find the reference
	
	
          cout << " \nFIFO Results " <<endl;
 
	for(framecount = 3; framecount <= 7; framecount++){ // Run the function for each frame
		page_fault = 0;
	for(j = 0; j < framecount; j++) // Set the references in the ram frame to -1
      {
            ram_frames[j] = -1;
      }
	for(j = 0; j < NUM_REF; j++){ //  iterate through references
		found = 0;
	
		for(i = 0; i < framecount; i++){ // Go through frames
			
		
		
			if(ref[j] == ram_frames[i]){ //Check if reference is there
			page_fault--;
			found++;
			}
		}	
	
		page_fault++;
	
	    if((page_fault <= framecount) && framecount == 0) // Check the initally empty ram_frames array 
            {
                  ram_frames[i] = ref[i];
			
            } 
            else if(found == 0) // If the reference is not there
            {
            ram_frames[(page_fault - 1) % framecount] = ref[j]; // Place the reference where the first reference that went in was
		
            }
			
		
        }
	if(page_fault < FIFOMin){	
		        frameMinFIFO = framecount;
				FIFOMin = page_fault;
			}
	cout<< "Frame Number " << framecount << ": " << page_fault << " Page Faults" << endl;
      }
}
void LRU_Sim(){
	     int lastUsed[NUM_REF];
	     int i, lruFrameCount;
	     int page_fault = 0;
             int min;
             int found;
	    cout << "LRU Results: " << endl;
            for(lruFrameCount = 3; lruFrameCount <= 7; lruFrameCount++)
	    {
				page_fault = 0;
           	 for(i=0;i< lruFrameCount;i++)
           	 {
            	ram_frames[i]=-1;
            	lastUsed[i] = 0; //it will keep the track of when the page was last used
           	 }
            i=0;
            while(i< NUM_REF)
            {
                int j=0;
		found=0;
                while(j< lruFrameCount)
                {
                	if(ref[i]==ram_frames[j]){ // check whether the page already exist in frames or not
                		found++;
                		lastUsed[j]=i+1; // incremenet when it was last used as a priority for searching
                }
                	j++;
                }   
                j=0;   // reset frame counter
     
                if(found==0) // if it's not found in the frames
                { 
                min=0;
		int x=0; 
                while(x < lruFrameCount-1) 
                { 
                    if(lastUsed[min]>lastUsed[x+1]) // Find the LRU page
                    	min=x+1;
                    x++;
					
                    }
                ram_frames[min]=ref[i];   // set the minimum value, starting with 0 equal to the current index of the reference to add to frames
                lastUsed[min]=i+1;  //Increase the minimum value of the LRU index since a reference was just put into the array
                page_fault++;           //increment the page fault
                }
            i++; 
            }
			if(page_fault < LRUMin){	
				LRUMin = page_fault;
				frameMinLRU = lruFrameCount;
				
			}
	    cout << "Frame Number " << lruFrameCount << ": " << page_fault << " Page Faults" << endl;
				
				
			
			}
}
void Print_Results(){
if(frameMinLRU < frameMinFIFO){
	cout << "Minimum Page Fault: Algorithm [LRU] with " << LRUMin << " and Frame Number " << frameMinLRU << endl;
}
else if(frameMinFIFO < frameMinLRU){
	cout << "Minimum Page Fault: Algorithm [FIFO] with " << FIFOMin << " and Frame Number " << frameMinFIFO << endl;
}
	else if(frameMinFIFO == frameMinLRU){
		cout << "Both Algorithms have the minimum page fault " << FIFOMin << " Page Faults" << " at Frame " << frameMinFIFO << endl;
	}
}
