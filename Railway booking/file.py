class fileSys:
    lower=[]
    l_count=10
    upper=[]
    u_count = 1
    middle=[]
    m_count = 1
    rac=[]
    r_count=1
    wait=[]
    w_count=1

    def add_l(self,x):
        self.lower.append(x)
        self.l_count -= 1

    def add_u(self, x):
        self.upper.append(x)
        self.u_count -= 1

    def add_m(self, x):
        self.middle.append(x)
        self.m_count -= 1

    def add_r(self, x):
        self.rac.append(x)
        self.r_count -= 1

    def add_w(self, x):
        self.wait.append(x)
        self.w_count -= 1
    def printStack(self):
        for i in self.lower:
            print(i.name,end=" ")
            print(i.berth_pref, end=" ")
        print("")
        for i in self.upper:
            print(i.name, end=" ")
            print(i.berth_pref, end=" ")
        print("")
        for i in self.middle:
            print(i.name, end=" ")
            print(i.berth_pref, end=" ")
        print("")
        for i in self.rac:
            print(i.name, end=" ")
            print(i.berth_pref, end=" ")
        print("")
        for i in self.wait:
            print(i.name, end=" ")
            print(i.berth_pref, end=" ")


    def cancel(self,name,berth):
        if(berth=="l"):
            idx=-1
            for i in range(len(self.lower)):
                if(self.lower[i].name == name):
                    idx=i
            if(idx != -1):
                self.lower.pop(i)
                self.l_count+=1
                if(len(self.rac)>0):
                    lucky = self.rac[0]
                    self.rac.pop(0)
                    lucky.berth_pref="l"
                    self.add_l(lucky)
                    if(len(self.wait) > 0):
                        luck = self.wait[0]
                        self.wait.pop(0)
                        self.w_count += 1
                        luck.berth_pref="r"
                        self.add_r(luck)

        elif(berth=="m"):
            idx = -1
            for i in range(len(self.middle)):
                if(self.middle[i].name == name):
                    idx = i
            if(idx != -1):
                self.middle.pop(i)
                self.m_count += 1
                if(len(self.rac) > 0):
                    lucky = self.rac[0]
                    self.rac.pop(0)
                    self.r_count+=1
                    lucky.berth_pref = "m"
                    self.add_m(lucky)
                    if(len(self.wait)>0):
                        luck=self.wait[0]
                        self.wait.pop(0)
                        self.w_count+=1
                        luck.berth_pref = "r"
                        self.add_r(luck)
        elif(berth=="u"):
            idx = -1
            for i in range(len(self.upper)):
                if(self.upper[i].name == name):
                    idx = i
            if(idx != -1):
                self.upper.pop(i)
                self.u_count += 1
                if(len(self.rac) > 0):
                    lucky = self.rac[0]
                    self.rac.pop(0)
                    lucky.berth_pref = "u"
                    self.add_u(lucky)
                    if(len(self.wait) > 0):
                        luck = self.wait[0]
                        self.wait.pop(0)
                        self.w_count += 1
                        luck.berth_pref = "r"
                        self.add_r(luck)
            
