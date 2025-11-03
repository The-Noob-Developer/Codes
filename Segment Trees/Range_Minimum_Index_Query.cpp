#include <bits/stdc++.h>
using namespace std;
void buildSegTree(int left,int right,int index,vector<int>&segmentTree,vector<int>&arr){
    if(left == right){
        segmentTree[index] = left;
        return;
    }
    int mid = left + (right - left)/2;
    buildSegTree(left,mid,2*index+1,segmentTree,arr);
    buildSegTree(mid+1,right,2*index+2,segmentTree,arr);
    if(arr[segmentTree[2*index+1]] < arr[segmentTree[2*index+2]])
        segmentTree[index] = segmentTree[2*index+1];
    else
        segmentTree[index] = segmentTree[2*index+2];
}
int query(int s,int e,int index,int l,int r,vector<int>&segmentTree,vector<int>&arr){

    // out of bound
    if(r<s || l>e){
        return -1;
    }

    // totally in bound
    if(l>=s && r<=e){
        return segmentTree[index];
    }
    // partially in bound
    int mid = l + (r - l) / 2;
    int leftMinIndex = query(s,e,2*index+1,l,mid,segmentTree,arr);
    int rightMinIndex = query(s,e,2*index+2,mid+1,r,segmentTree,arr);
    if(leftMinIndex==-1) return rightMinIndex;
    if(rightMinIndex==-1) return leftMinIndex;
    if(arr[leftMinIndex] < arr[rightMinIndex]) return leftMinIndex;
    else return rightMinIndex;
}

void updateRE(int index,int val,vector<int>&segmentTree,vector<int>&arr,int i,int l,int r){
        if(l==r){
            if(index!=l) return;
            // segmentTree[i] = val; -> NO NEED TO WRITE COZ SEG TREE ALREADY STORES INDEX
            arr[index] = val; // JUST UPDATE THE ARRAY
            return;
        }
        int mid = l + (r-l)/2;
        if (index <= mid)
            updateRE(index, val, segmentTree,arr, 2 * i + 1, l, mid);
        else
            updateRE(index, val, segmentTree,arr, 2 * i + 2, mid + 1, r);
        if(arr[segmentTree[2*i+1]] < arr[segmentTree[2*i+2]])
            segmentTree[i] = segmentTree[2*i+1];
        else
            segmentTree[i] = segmentTree[2*i+2];
        
    }
void update(int index, int val,vector<int>&segmentTree,vector<int>&arr) {
    updateRE(index,val,segmentTree,arr,0,0,arr.size()-1);
}
int main() {
	int n,q;
    cin>>n>>q;
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<int>segmentTree(4*n,1e9);
    buildSegTree(0,n-1,0,segmentTree,arr);
    for(int i=0;i<q;i++){
        char ch;
        int l,r;
        cin>>ch>>l>>r;
        if(ch=='q'){
            cout<<arr[query(l-1,r-1,0,0,n-1,segmentTree,arr)]<<endl;
        }
        else{
            update(l-1,r,segmentTree,arr);
        }
    }
    return 0;
}