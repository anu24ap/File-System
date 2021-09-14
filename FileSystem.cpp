//Code developed in Dev-C++ 5.11

#include<iostream>
#include<bits/stdc++.h>
#include<string>

using namespace std;

struct inode
{
  char name[8];
  int size;
  int blockPointers[8];
  int used = 0;
};

struct superBlock
{
  char is_empty[128];
  struct inode index[16];
};

struct Data_block
{
 char block[1024];
};

struct superBlock super;
struct Data_block Data[127];


void create(char name[], int size)
{
	  int i=0;
      while(i<16)              
      {
        if((strcmp(name,super.index[i].name) == 0)&&(super.index[i].used==1))
        {
           cout<<name<<" file already exist, can't create another file with same name\n";
           return;
        }
        i++;
      }
      
      int file_space = -1;
      
      for(int i=0;i<16;i++)                              
      {
          if(super.index[i].used==0)
          {
             file_space = i;
             break;
          }
      }

      if(file_space==-1)
      {
        cout<<"File system is already full, so can't create "<<name<<" file\n";
        return;
      }
      
      int reqdBlock = 0;
      for(int i=1 ;i <128 ;i++)                   // Number of required empty blocks exist or not
      {
        if(super.is_empty[i]=='0')
        reqdBlock++;

       }

       if(reqdBlock<size)
       {
         cout<<"Number of blocks required for "<<name<<" file is higher than the number of empty blocks, so cant create this file\n";
         return;
       }

       strcpy(super.index[file_space].name, name);         // create the file with this name;
       super.index[file_space].size = size ;
       reqdBlock=0;
       i=1;
       while(reqdBlock!=size)
       {
         if(super.is_empty[i]=='0')
         {
             super.is_empty[i]='1';
             super.index[file_space].blockPointers[reqdBlock]=i;
             reqdBlock++;
         }
          i++;
       }

        super.index[file_space].used=1;
        cout<<name<<" file created succesfully \n";

   };

void initialize()
{
   	  int idx=0;
      while(idx<128)
      {
         super.is_empty[idx]='0';
         idx++;
      }
   }

void Delete(char name[])                    //Delete the file
{
      for(int i=0; i<16;i++)               // Any file with this name already exist or not
      {
        if((strcmp(name,super.index[i].name) == 0)&&(super.index[i].used==1))
        {
           super.index[i].used=0;
           for(int j=0; j<super.index[i].size;j++)
           {
              super.is_empty[super.index[i].blockPointers[j]]='0';
           }
           cout<<name<<" file deleted successfully\n";
           return;
        }
      }
      cout<<name<<" file doesn't exist, so unable to delete\n";
}

void read(char name[] , int blockno, char buffer[])                    // Read the particular block
{
    for(int i=0; i<16;i++)
    {
    	if((strcmp(name,super.index[i].name) == 0)&&(super.index[i].used))
        {
        
           if(blockno>=super.index[i].size)
           cout<<"Block is inaccessible, number of blocks allocated is less than block number\n";
           else
           {
           cout<<"Data read from "<<name<<" file at blockumber "<<blockno<<" is = "<<Data[super.index[i].blockPointers[blockno]].block<<endl;
           strcpy(buffer, Data[super.index[i].blockPointers[blockno]].block);}
           return;
        }
      }
      cout<<name<<" file doesn't exist, so unable to read\n";

   }


void write(char name[], int blockno, char buf[])
    {
		  int i=0;
          while(i<16)
      {
        if((strcmp(name,super.index[i].name) == 0)&&(super.index[i].used))
        {
            if(blockno>=super.index[i].size)
           cout<<"Block is inaccessible, number of blocks allocated is less than block number\n";
           else{
           strcpy(Data[super.index[i].blockPointers[blockno]].block,buf);
           cout<<"Write is successfull\n";}
           return;
        }
        i++;
      }
      cout<<name<<" file doesn't exist, so unable to write\n";
    }

void ls()
    {
         for(int i=0;i<16;i++)
         {
            if(super.index[i].used==1)
            {
               cout<<"File name = "<<super.index[i].name<<"  size = "<<super.index[i].size<<endl;
            }
         }

}

int main()
{
  initialize();

  int n=1;
  
  while(n)
  {
    cout<<"1.Create a file \n";
    cout<<"2.Delete a file \n";
    cout<<"3.Read a file \n";
    cout<<"4.Write into a file \n";
    cout<<"5.Print all files \n";
    cout<<"Enter 0 to exit \n";
    cout<<"Choose one of the above options ";
    cin>>n;

    if(n==1)
    {
      cout<<"Enter the name of file: ";
      char str[8];
    
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the size of file: ";
      int size;
      cin>>size;
      if(size>8)
      cout<<"Creating a file of size more than 8 blocks is not allowed\n";
      else
      create(str, size);
    }

    else if(n==2)
    {
      cout<<"Enter the file name: ";
      char str[8];

      cin.ignore(256, '\n');
      cin.getline(str, 8);
      Delete(str);
    }

    else if(n==3)
    {
      cout<<"Enter the file name: ";
      char str[8];
    
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the block number: ";
      int block;
      cin>>block;
      char buf[1024];
      read(str, block , buf);
    }

    else if(n==4)
    {
      cout<<"Enter the file name: ";
      char str[8];
      cin.ignore(256, '\n');
      cin.getline(str, 8);
      cout<<"Enter the block number: ";
      int block;
      cin>>block;
      char buf[1024];
      cout<<"Enter the contents to write into the file: ";
      cin.ignore(256, '\n');
      cin.getline(buf, 1024);
      write(str, block , buf);

    }

    else if(n==5)
    {
      ls();
    }
    cout<<endl;
  }
  
  return 0;
}
