netsh wlan show profiles
netsh wlan show profile name=" aici se introduce numele netului" key=clear | findstr "clé"
sau mai bine 
netsh wlan show profile name="Bbox-346E" key=clear | findstr "key content"


net start dot3svc 
