# include <iostream>
# include <vector>
using namespace std;

void heapify(vector<int>& heap, int curr, int size){
    int largest = curr;
    int left = 2*curr + 1;
    int right = 2*curr + 2;

    if(left < size and heap[left] > heap[largest])
        largest = left;
    if(right < size and heap[right] > heap[largest])
        largest = right;
    if(largest != curr){
        int temp = heap[curr];
        heap[curr] = heap[largest];
        heap[largest] = temp;

        heapify(heap, largest, size);
    }
}

void heapSort(vector<int>& heap){
    for(int i = heap.size()/2 - 1; i >= 0; i--)
        heapify(heap, i, heap.size());

    for(int i = heap.size() - 1; i > 0; i--){
        int temp = heap[0];
        heap[0] = heap[i];
        heap[i] = temp;

        heapify(heap, 0, i);
    }
}

int main(){
    vector<int> heap{9, 6, 8, 21, 11, 4, 3};
    heapSort(heap);

    cout << "Heap in ascending order : \n";
    for(int i = 0; i < heap.size(); i++)
        cout << heap[i] << " ";
    
    return 0;
    
}
