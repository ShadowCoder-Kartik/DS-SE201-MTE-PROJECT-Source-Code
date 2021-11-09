#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
using namespace std;

//DS MTE PROJECT 
//CODE FOR CONSTRUCTION OF WAVELET TREE

//Submitted By - Madhav Khattar 2K20/SE/78 && Kartik Gupta 2K20/SE/71


//____________________________________________________________________________________________________
// some helper functions used

void insertion_sort(int* a, int n);  // function to sort array

int get_maximum(int * a, int size);  // to get maxima from an array

int get_minimum(int* a, int size);   // to get minima from array

//_______________________________________________________________________________________________________
// making our class

class wavelet_tree {  // basic structure of our class

    public:  // members of the class

    vector<int> freq;  // to store the frequency of characters

    wavelet_tree* left_subtree, *right_subtree;  //subtree of our wavelet tree
 
    int min, max;  // min and max values present in the array passed

    wavelet_tree(int* start, int* end, int min, int max);  // parameterized constructor to make wavelet tree
};

//________________________________________________________________________________________________________________
 
// main program

int main(){

    cout<<endl<<"\t\t\tDS MTE PROJECT CODE"<<endl<<endl;
    cout<<"\t\t   CONSTRUCTION OF WAVELET TREE"<<endl<<endl<<endl;

    int n;
    cout<<"Enter the size of array : ";
    cin>>n;

    cout<<endl<<"Enter the "<<n<<" elements : ";
    
    int* a = new int[n]; // array declaration
    
    for(int i=0;i<n;++i){ // taking input in array

        cin>>a[i];
    }

    insertion_sort(a,n); // sorting the array

    int maximum = get_maximum(a,n);  // finding maxima

    int minimum = get_minimum(a,n);  // finding minima

    cout<<endl<<endl<<"Printing the Wavelet Tree (from bottom to top) : ";
    cout<<endl<<endl;

    wavelet_tree root (a, a + n, minimum, maximum);  //creating object of our class

    return 0;
}

//___________________________________________________________________________________________________________________-

// functions are defined here

void insertion_sort(int* a, int n){  // function to sort array

    for(int i=1;i<n;++i){

        int key = a[i];

        int j=i;
        while(j>0 && a[j-1]>key){
            a[j] = a[j-1];
            --j;
        }

        a[j] = key;
    }

}


int get_maximum(int * a, int size){  // to get maxima from an array

    int max = a[0];

    for(int i=1;i<size;++i){
        if(a[i]>max){
            max = a[i];
        }
    }

    return max;

}

int get_minimum(int* a, int size){  // to get minima from array

    int min = a[0];

    for(int i=1;i<size;++i){
        if(a[i]<min){
            min = a[i];
        }
    }

    return min;

}


wavelet_tree::wavelet_tree(int* start, int* end, int min, int max){  // function to make wavelet tree

    this->min = min;  // initializing the values
        this->max = max;  // initializing the values
  
        if (start >= end){  // in case the array is NULL
            return;
        }
 
        else if (max == min) {  // if the array entered contains equal values
 
            freq.push_back(0);     

            auto it = start;

            while(it!=end){ // tree will not have any child since data is homogeneous

                 freq.push_back(freq.back() + 1);

                 ++it;

            }              
  
            return;
        }

        else{ 
 
        int mid = (min + max) / 2;  // calculating middle value

        freq.reserve(end - start + 1); // reserving space = number of key values per node
 
        freq.push_back(0);
 
        for (auto it = start; it != end; it++){   // adding values to frequency vector
            
            if((*it)<= mid){   // checking if value is less than or equal to mid

            freq.push_back(freq.back() + 1 );

            }

        }
        
        // for(int i=0;i<freq.size();++i){
        //     cout<<freq[i]<<" ";
        // }

 
        auto separator = stable_partition(start, end, [mid](int x){   // lambda function
            return x<=mid;
        });
 
        left_subtree = new wavelet_tree(start, separator, *start, *(separator-1));  // recursive call to make left sub-tree
        if(start!= separator){
        cout<<"Left: ";                             // 
        for(auto i=start; i!=separator; ++i){       // printing the left sub-tree
            cout<<*i<<" ";                          //
        }                                           //

        cout<<endl;}

        right_subtree = new wavelet_tree(separator, end, *separator, max);  // recursive call to make right sub-tree
        
        if(separator!=end){
        cout<<"Right: ";                          //
        for(auto i=separator;i!=end;++i){         // printing the right sub-tree
            cout<<*i<<" ";                        //
        }                                         //

        cout<<endl<<endl;
        }

        }

}
//___________________________________________________________________________________________________________________________