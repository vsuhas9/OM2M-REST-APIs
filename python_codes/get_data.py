from oneM2M_functions import *

server = "http://127.0.0.1:8080"
cse = "/~/in-cse/in-name/"
ae = "AE-TEST-PY"
container_name = "Data"

# ------------------------------------------
# Fill code here to get latest content_instance
# specified by the URI
# ------------------------------------------
ret_code, latest_data = get_data(server+cse+ae+"/Node-1/Data/la")
print(latest_data)
# ------------------------------------------

# ------------------------------------------
# Fill code here to get oldest content_instance
# specified by the URI
# ------------------------------------------
# ret_code, oldest_data = get_data(server+cse+ae+"/Data/ol")
# print(oldest_data)
# ------------------------------------------

# ------------------------------------------
# Fill code here to get all content_instances
# specified by the URI
# Note: change the return statement as given in get_data function inside the oneM2M_functions.py
# ------------------------------------------
# ret_code, all_data = get_data(server+cse+ae+"/Data?rcn=4")
# print(all_data)
# ------------------------------------------
