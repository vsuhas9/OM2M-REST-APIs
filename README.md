# Intro To IoT

# OM2M
* Download the latest version of OM2M platform: https://wiki.eclipse.org/OM2M/Download

# POSTMAN
* Download and install the POSTMAN REST client: http://www.postman.com

# POSTMAN_collection 
* The postman collection is inside POSTMAN_collection
* Import the collection in POSTMAN as explained in: https://apitransform.com/how-to-import-a-collection-into-postman/
* To create the resource tree, send the POST requests (create ae > create cnt > create cin)

# nodeMCU_codes
* Basic source codes are inside nodeMCU_codes

# python_codes
* Basic source codes to create the resource tree
* Install the "requests" and "json" modules (skip this step if already installed)
* Run create_resource_tree.py to create the oneM2M resource tree
* Run get_data.py to retrieve data from OM2M platform using REST APIs
* Run delete_resource.py, if you want to delete particular resource 

# Resource Tree Creation
* Start the OM2M platform by executing the "start.bat" script on Windows or "start.sh" on Linux and Mac OS.
* Run create_resource_tree.py to create the oneM2M resource tree 
* Open http://127.0.0.1:8080/webpage in browser.
* Enter username:password = admin:admin
* You should see the resource tree ![sample_resource_tree.png](https://github.com/shubham-mante/esw-iiith/blob/main/images/sample_resource_tree.png)

