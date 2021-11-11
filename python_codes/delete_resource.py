from oneM2M_functions import *

server = "http://127.0.0.1:8080"
cse = "/~/in-cse/in-name/"
ae = "Test-1"
container_name = "Data"

# ------------------------------------------
# Fill code here to delete a oneM2M resource (AE/CNT/CIN)
# example deleting the Data container
delete(server+cse+ae+"/Data")
# ------------------------------------------
