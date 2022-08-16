from file import fileSys
from passeng import Passenger

master=fileSys()

while(True):
    opt = int(input('1.Book\n2.Cancel\n3.Exit'))
    master.printStack()
    if(opt==1):
        name=input("Name: ")
        age=int(input("Age: "))
        pref = input("Preference: ")
        temp=Passenger(name,age,pref)
        if(pref=="l"):
            if(master.l_count > 0):
                master.add_l(temp)
            elif(master.m_count > 0):
                temp.berth_pref = "m"
                master.add_m(temp)
            elif(master.u_count > 0):
                temp.berth_pref = "u"
                master.add_u(temp)
            elif(master.r_count > 0):
                temp.berth_pref = "r"
                master.add_r(temp)
            elif(master.w_count > 0):
                temp.berth_pref = "w"
                master.add_w(temp)
            else:
                print('no ticket')
            continue

        if(pref == "m"):
            if(master.m_count > 0):
                master.add_m(temp)
            elif(master.l_count > 0):
                master.add_l(temp)
            elif(master.u_count > 0):
                master.add_u(temp)
            elif(master.r_count > 0):
                master.add_r(temp)
            elif(master.w_count > 0):
                master.add_w(temp)
            else:
                print('no ticket')
            continue

        if(pref == "u"):
            if(master.u_count > 0):
                master.add_u(temp)
            elif(master.l_count > 0):
                master.add_l(temp)
            elif(master.m_count > 0):
                master.add_m(temp)
            elif(master.r_count > 0):
                master.add_r(temp)
            elif(master.w_count > 0):
                master.add_w(temp)
            else:
                print('no ticket')
            continue
    elif(opt==2):
        name=input("name: ")
        berth=input("berth: ")
        master.cancel(name,berth)
    elif(opt==3):
        break

master.printStack()







        
