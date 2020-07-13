import zoo

# Create an animal.
animal = zoo.Animal("dog")
# The Python object.
print(animal)
# Use the exposed method to show the address of the C++ object.
print("The C++ object is at 0x%016x" % animal.get_address())
# Use the exposed property accessor.
print("I see a \"%s\"" % animal.name)
animal.name = "cat"
print("I see a \"%s\"" % animal.name)