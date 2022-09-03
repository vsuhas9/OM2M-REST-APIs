rmdir /S /Q iiith_env
py -m pip install --user virtualenv
py -m venv iiith_env
.\iiith_env\Scripts\activate && pip install -r requirements.txt && start cmd.exe /k "jupyter notebook --port=5090"