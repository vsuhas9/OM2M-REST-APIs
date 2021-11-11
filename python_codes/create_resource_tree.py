from oneM2M_functions import *

server = "http://127.0.0.1:8080"
cse = "/~/in-cse/in-name/"


# ------------------------------------------
# Fill code here to create AE
# specified by the URI
# ------------------------------------------
ae = "Test-1"
lbl_ae = ["AE-Label-1", "AE-Label-2"]
create_ae(server+cse, ae, lbl_ae)
# ------------------------------------------


# ------------------------------------------
# Fill code here to create container in the AE
# specified by the URI
# ------------------------------------------
container_name = "Data"
lbl_cnt = ["CNT-Label-1", "CNT-Label-2"]
create_cnt(server+cse+ae, container_name, lbl_cnt)
# ------------------------------------------


# ------------------------------------------
# Fill code here to create content_instance
# specified by the URI
# ------------------------------------------
content_instance = 0
lbl_cin = ["CIN-Label-1", "CIN-Label-2"]
create_data_cin(server+cse+ae+"/"+container_name, content_instance, lbl_cin)
# ------------------------------------------

