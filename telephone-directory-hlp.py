from collections import defaultdict

count = 0

class HashLinearProbing:
    def __init__(self, size):
        self.hash_table = defaultdict(list)

        for itr in range(size):
            self.hash_table[itr] = []

        print(self.hash_table)
    
    def hashing(self, name):
        ascii_sum = 0

        for itr in range(0, len(name)):
            ascii_sum = ascii_sum + ord(name[itr])  # Adding the ASCII values of all the letters in the string
        
        return(ascii_sum % size) # Returning the modulo value of ASCII Sum and the size of the table

    def insertIntoHashIndexWithoutReplacement(self, name, index, phone_no):
        global count

        load_factor = ((count / size) * 100)

        if load_factor < 80:
            if len(self.hash_table[index]) == 0:
                self.hash_table[index].append(name)
                self.hash_table[index].append(phone_no)
                count = count + 1
            else:
                self.findVacantIndex(name, index)
        else:
            print("Cannot enter the key since the hash table is almost full.")

    def insertIntoHashIndexWithReplacement(self, key, index):
        if self.hash_table[index] == -1:
            self.hash_table[index] = key
        elif index == self.hashing(self.hash_table[index]):
            self.findVacantIndex(key, index)
        else:
            temp = self.hash_table[index]
            self.hash_table[index] = key
            self.findVacantIndex(temp, index)
        
    def findVacantIndex(self, key, index):
        for i in range(1, size):
            pos = (index + 1) % size
            if self.hash_table[pos] == -1:
                self.hash_table[pos] = key
                break

    def display(self):
        print("Hash Table Keys")
        print(self.hash_table)

        for itr in self.hash_table.items():
            print(itr)

# ------------------------------------------------------ #

print("In main\n")
size = int(input("Enter the size of the telephone book: "))
hash_object = HashLinearProbing(size)

while 1:
    print("Enter 1 for without replacement, 2 for with replacement, 3 to search for a key, 4 to display the table and 5 to exit: ")
    user_choice = int(input("Enter the option: "))

    if user_choice == 1:    
        
        name = str.strip(input("Enter the name: "))
        name = name.upper()
        phone_no = int(input("Enter key phone number: "))
        index = hash_object.hashing(name)
        print(index)
        hash_object.insertIntoHashIndexWithoutReplacement(name, index, phone_no)    
        hash_object.display()
    
    elif user_choice == 2:

        key_value = int(input("Enter key value: "))
        index = hash_object.hashing(key_value)
        hash_object.insertIntoHashIndexWithReplacement(key_value, index)
        hash_object.display()
    
    elif user_choice == 3:
        key_value = int(input("Enter key value: "))
        # Search function
    elif user_choice == 4:
        hash_object.display()
    elif user_choice == 5:
        break
    else:
        print("Please enter a valid input.")

print("Thank you for using the Hash Linear Probing program.")




