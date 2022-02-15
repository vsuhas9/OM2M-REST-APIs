import gdown

url = 'https://drive.google.com/uc?export=download&id=1iy1fJFDfNj-wzO0RlDLuoCwePTyv85it&confirm=t'
output = 'OM2M.zip'
gdown.download(url, output, quiet=False)


