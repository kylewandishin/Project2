import sys

# Accessing command line arguments
arguments = sys.argv

# Checking the number of arguments
num_arguments = len(arguments)

# Processing the passed arguments
if num_arguments > 1:
    # The first argument (sys.argv[0]) is the script name
    # The following arguments are user-provided options
    options = arguments[1:]
    
    # Print the options
    print("Options provided:", options)
else:
    print("No options provided.")