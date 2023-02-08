/* This is skeleton code for the Two-Pass Multi-Way Merge Sort algorithm, you can make modifications as long as you meet 
   all question requirements*/  
// Currently, this program will just load the records into buffers (main memory) and print the records once the buffers 
// are filled. This process will continue until all of Emp.csv is read.

//#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <limits>
#include <sys/limits.h>

using namespace std;

//defines how many buffers are available in the Main Memory 
#define buffer_size 22
#define BLOCK_SIZE 56       //Size in bytes

const std::string sorted_fname = "EmpSorted.csv";
const std::string data_dir = "./data/";

unsigned int runs = 0;      //global for tracking runs


//The packing order of this struct could be better. It's not current alligned.
struct EmpRecord {
    int eid;
    string ename;
    int age;
    double salary;
};
EmpRecord buffers[buffer_size]; // this structure contains 22 buffers; available as your main memory.

// Grab a single block from the Emp.csv file. In theory, if a block was larger than
// one tuple, this function would return an array of EmpRecords (one block worth) 
// and the entire if-then-else statement would be wrapped in a loop that would read
// tuples in until the block size was hit.
EmpRecord Grab_Emp_Record(fstream &empin) {
    string line, word;
    EmpRecord  emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}

// Print whatever is stored in the buffers of Main Memory 
// Can come in handy to see if you've sorted the records in your main memory properly.
void Print_Buffers(int cur_size) {
    for (int i = 0; i < cur_size; i++)
    {
        cout << i << " " << buffers[i].eid << " " << buffers[i].ename << " " << buffers[i].age << " " << buffers[i].salary << endl;
    }
}


/*
 * Input: None,
 * Output: None,
 * Description: deletes the temp files used during sorting.
 */
void remove_temp_files(void) {
    std::cout << "remove_temp_files(), not yet implimented!" << std::endl;
}

/*
 * Input: Sorted Array of pointers to EmpRecords
 * Output: Returns 0 on sucess
 * Description: Stores the sorted blocks into temp files
 */
unsigned int store_in_tmp_files(EmpRecord *buff_seq[buffer_size]) {
    //create new file for this run.
    std::string tmp_filename = "./data/run_" + std::to_string(runs);
    
    //DEBUGGING
    std::cout << "filename: " << tmp_filename << std::endl;

    //open the file. No error checking at the moment. Not enough time.
    ofstream tmpfile;
    tmpfile.open(tmp_filename, ios::out | ios::app);

    //write to the file handle
    //This is a bit verbose, but I think it's very understandable in 
    //this format.
    for(int i = 0; i < buffer_size; i++) {
        tmpfile << std::to_string(buff_seq[i]->eid) + ",";
        tmpfile << buff_seq[i]->ename + ",";
        tmpfile << std::to_string(buff_seq[i]->age) + ",";
        tmpfile << std::to_string(buff_seq[i]->salary) + "\n";
    }

    //Close the file we just finished working with.
    tmpfile.close(); 
    
    //update the global runs.
    runs += 1;

    return 0;
}


// Sort the buffers in main memory based on 'eid' and then store those sorted records in
// a temporary file on disk (create a run and store it as a file on disk).
// You can change the return type and arguments as you see fit. 
void Sort_in_Main_Memory(){

    //create a list of pointers to the buffer.
    EmpRecord *buff_seq[buffer_size] = {};

    //Init the buffer sequence to the current order of them.
    for(int i = 0; i < buffer_size; i++) {
        //set the pointers to the addresses.
        buff_seq[i] = &buffers[i];
    }


    //Now we can start to sort the buffers/blocks in main memory.
    //We avoid having to do expensive copies by using pointers for our
    //buffer sequence instead of moving the stucts around.
    
    for(int i = 0; i < buffer_size - 1; i++) {
        for(int j = i+1; j < buffer_size; j++) {
            //check if we should swap the two based on size of ID.
            if(buff_seq[i]->eid > buff_seq[j]->eid) {
                //Then we swap the positions in the sequence buffer.
                EmpRecord *tmp = buff_seq[i];
                buff_seq[i] = buff_seq[j];
                buff_seq[j] = tmp;
            }
            else {
                continue;
            }
        }
        //End of for loop
    }
    //End of for loop

    //By now the pointers in the buff_seq array should be least to greatest.
    
    store_in_tmp_files(buff_seq);


}

//ideally this would have a check for the file and some exception handling
//but, meh. It's a one off and time crunch
void append_to_sorted(EmpRecord *smallest_record_ptr) {
    fstream sorted_file;
    
    //open in append mode.
    sorted_file.open(sorted_fname, ios::out | ios::app);
    
    sorted_file << std::to_string(smallest_record_ptr->eid) + ",";
    sorted_file << smallest_record_ptr->ename + ",";
    sorted_file << std::to_string(smallest_record_ptr->age) + ",";
    sorted_file << std::to_string(smallest_record_ptr->salary) + "\n";

    //close the file.
    sorted_file.close();
}


// Merges your M-1 runs (from disk) using the buffers in main memory and stores them in 
// a sorted file called 'EmpSorted.csv'(The Final Output File).
// You can change the return type and arguments as you see fit.
void Merge_Runs_in_Main_Memory(){
    
    //we use this to default the starting pointer to max possible eid
    EmpRecord bigest;
    bigest.eid = INT_MAX;
    
    //Keep looping until all the emp.eid values show endof file.
    while(true) {
        //more pointer crud, allows us to avoid actually moving structs around.
        EmpRecord *smallest_record_ptr;

        //do this for all the possible records from the runs.

        //Read in a block for each run.
        for(int i = 0; i <= runs; i++) {
            std::string fname = "run_" + std::to_string(i);
            fstream run_file;
            run_file.open(fname, ios::in);
          
            //need to check for eof

            //store the block/record in this case into the buffer that matches i. 
            buffers[i] =  Grab_Emp_Record(run_file);
        }

        //Now sort through the availble ones.
        for(int i = 0; i < buffer_size; i++) {
            
            //init the smallest_record_ptr and account for the
            //possibility that the current buffer index is a EOF
            if(buffers[i].eid >= 0)
                smallest_record_ptr = &buffers[i];
            else
                smallest_record_ptr = &bigest;
            
           
            //loop and compare current smallest to all other eids in buffers 
            for(int j = i+1; j < buffer_size; j++) {

                //check that the buffer for a run hasn't run out.
                if(buffers[i].eid == -1) {
                    continue;
                }


                //If it's smaller than the rest, we point to it.
                else if(smallest_record_ptr->eid > buffers[j].eid) {
                    smallest_record_ptr = &buffers[j];
                }

                //Nothing to do, already found the correct record.
                else {
                    continue;
                }
            }//END OF FOR LOOP 1
        }//END OF FOR LOOP 0
        
        //check if we have emptied all the runs.
        //we can tell, by the smallest_record_ptr showing max value.
        if(smallest_record_ptr->eid == INT_MAX) {
            break;
        }
        //now that we have the smallest one, we toss it into the file.
        append_to_sorted(smallest_record_ptr);

    }//END OF WHILE LOOP
    //at this point all the stuff should be done.
}

int main() {
    // open file streams to read and write
    fstream input_file;
    input_file.open("./data/Emp.csv", ios::in);
 
    // flags to check when relations are done being read
    bool flag = true;
    int cur_size = 0;
    
    /*First Pass: The following loop will read each block, put it into main_memory,
        sort them, and then will put write them to a temporary file (as a run) for 2nd pass */
    while (flag) {
      // FOR BLOCK IN RELATION EMP

      // grabs a block
      EmpRecord  single_EmpRecord  = Grab_Emp_Record(input_file);
      // checks if filestream is empty
      if (single_EmpRecord.eid == -1) {
          flag = false;
          Print_Buffers(cur_size); // The main_memory is not filled up but there are some leftover tuples that need to be sorted.
      }
      if(cur_size + 1 <= buffer_size){
          // Memory is not full. Store the current record into a buffer.
          buffers[cur_size] = single_EmpRecord ;
          cur_size += 1;
      }
      else{
          // Memory is now full. Sort the tuples in Main Memory and store them in a temporary file (runs)
          cout << "Main Memory is full. Time to sort and store sorted blocks in a temporary file" << endl;
          //Print_Buffers(buffer_size);
          //SortMain("Attributes You Want");
          Sort_in_Main_Memory();   

          // After sorting, start again. Clear memory and put the current tuple into main memory.
          cur_size = 0;
          buffers[cur_size] = single_EmpRecord;
          cur_size += 1;
        }
      
    }//END OF WHILE
    input_file.close();
  
    /* Implement 2nd Pass: Read the temporary sorted files (runs) and sort them as discussed in class. 
     Write the final output (fully sorted Emp relation) to EmpSorted.csv*/
    
    // Uncomment when you are ready to store the sorted relation
    // fstream sorted_file;  
    // sorted_file.open("EmpSorted.csv", ios::out | ios::app);

    // Pseudocode
    //bool flag_sorting_done = false;
    //while(!flag_sorting_done){
    //    Merge_Runs_in_Main_Memory();
    //    break;
    //}


    //I just decided to keep all the merge handling in their own functions.
    Merge_Runs_in_Main_Memory();    

    // You can delete the temporary sorted files (runs) after you're done in order to keep things clean and tidy.
    remove_temp_files();
  return 0;
}
