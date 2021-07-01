from collections import defaultdict
count=0
class LinearProbing:
    hash_table=defaultdict(int)
    def __init__(self,size):
        self.size=size
        
        for i in range(self.size):
            self.hash_table[i]=-1
    
    def hash_function(self,key):
        return (key%size)
            
    def insert_data_with_replacement(self,key):
        pos=self.hash_function(key)
        if(self.hash_table[pos]==-1):
            self.hash_table[pos]=key
            
        else:
            if(pos==self.hash_function(self.hash_table[pos]%size)): 
                self.find_index(key,pos)
                
            else:
                curr=self.hash_table[pos]
                self.hash_table[pos]=key
                self.find_index(curr,pos)
                
    def find_index(self,key,pos):
        index=pos+1
        for i in range(1,size):
            if(self.hash_table[index%size]==-1):
                self.hash_table[index%size]=key
                break
            index+=1
                
        
    def insert_data(self,key):
        global count
        count+=1
        pos=self.hash_function(key)
        if(self.hash_table[pos]==-1):
           self.hash_table[pos]=key
        else:
            index=pos+1
            for i in range(1,size):
                if(self.hash_table[index%size]==-1):
                   self.hash_table[index%size]=key
                   break
                index+=1
    def display(self):
        print("Hash Table-->",self.hash_table)
        
    def load_factor(self):
        print(count/size*100)
            
size=int(input("Enter the size of hash table"))            
obj=LinearProbing(size)
print("Enter the keys")
while True:
    key=int(input())
    if(key==-1):
        break;
    
    # obj.insert_data_with_replacement(key)
    obj.insert_data(key)

obj.display()



