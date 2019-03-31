#include <iostream> 
#include <cstdlib> 
#include<fstream>

std::ofstream fcout;
using namespace std; 

// A Huffman tree node 
struct MinHeapNode { 
	char data; 
    int freq; 
	// Left and right child 
	struct MinHeapNode *left, *right; 
}; 

//Collection of min heap (or Hufmman tree) nodes 
struct MinHeap { 
	int size;// Current size of min heap  
	int capacity;// capacity of min heap  
	struct MinHeapNode** array; 
}; 

//allocate a new min heap node with given character and frequency of the character 
struct MinHeapNode* newNode(char data, int freq) 
{ 
	struct MinHeapNode* temp 
		= (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

//to create a min heap of given capacity 
struct MinHeap* createMinHeap(int capacity)
{ 

	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	// current size is 0 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

//to swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// The minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int index) 
{ 
	int smallest = index; 
	int left = 2 * index + 1; 
	int right = 2 * index + 2; 

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != index) { 
		swapMinHeapNode(&minHeap->array[smallest],&minHeap->array[index]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// A function to extract minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 
	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

//to insert a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) 
{ 
	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    { 
		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

// Creates a min heap of capacity = size and inserts all character in min heap
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 
{ 
	struct MinHeap* minHeap = createMinHeap(size); 
	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 

	int i; 
	for (i = (size - 2) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 

	return minHeap; 
} 

//Builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 
{ 
	struct MinHeapNode *left, *right, *top; 

	//Create a min heap of capacity equal to size. Initially, there are modes equal to size. 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 

	// Iterate while size of heap doesn't become 1 
	while (minHeap->size != 1) { 

		//Extract the two minimum freq items from min heap 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		//Create a new internal node with frequency equal to the sum of the two nodes frequencies. Make the two extracted node as left and right children of this new node 
		top = newNode('$', left->freq + right->freq); 
		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	//The remaining node is the root node and the tree is complete. 
	return extractMin(minHeap); 
} 

// Prints huffman codes from the root of Huffman Tree 
void printCodes(struct MinHeapNode* root, int arr[], int top) 
{ 
	// Assign 0 to left edge and recur 
	if (root->left) { 

		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	// Assign 1 to right edge and recur 
	if (root->right) { 

		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 

	// If this is a leaf node, then it contains one of the input characters, print the character and its code from arr[] 
	if (!(root->left) && !(root->right)) { 

		cout<< root->data <<": "; 
		
        int i; 
	    for (i = 0; i < top; ++i) 
		    cout<< arr[i]; 
        cout<<"\n"; 
	} 
} 

void output(struct MinHeapNode* n){
    if(n->left!=NULL){
        fcout<<n->freq<<"->"<<n->left->freq<<";"<<endl;
        output(n->left);
           }
       if(n->right!=NULL){
        fcout<<n->freq<<"->"<<n->right->freq<<";"<<endl;
        output(n->right);
           }
}

//Builds a Huffman Tree and print codes by traversing the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size) 
{ 
	// Construct Huffman Tree 
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size); 

	int arr[100], top = 0; 
    cout<<endl<<"Huffman Codes : "<<endl;
	printCodes(root, arr, top); 
    fcout.open("sample.dot.txt");
    fcout<<"digraph{"<<endl;
    output(root);
    fcout<<"}"<<endl;
} 

int main() 
{ 
    int n;
    cout<<"Enter the number of characters : ";
    cin>>n;

    cout<<"Enter character, frequency : "<<endl;
    char *arr = new char[n];
    int *freq = new int[n];
	for(int i=0;i<n;i++)
    {
        cin>>arr[i]>>freq[i];
    }

	HuffmanCodes(arr, freq, n); 

	return 0; 
} 
//6 a 5 b 9 c 12 d 13 e 16 f 45