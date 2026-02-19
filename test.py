import sys
import os
from tqdm import tqdm
import random

sys.path.append('./build')
build_dir = os.path.abspath('./build') 
os.add_dll_directory(build_dir)

import tsn 

def check_overlap(messages,results):
    hyper_period = output.hyperperiod
    time = [dict() for i in range(hyper_period)]

    for msg in range(len(results.amount_sent)):
        for rep in range(len(results.amount_sent[msg])):
            for i in range(len(results.R[(msg,rep)])):

                route = results.R[(msg,rep)][i]
                start_time = results.departure_times[(msg,rep)][i]
                for idx in range(len(route) - 1):
                    u = min(route[idx],route[idx+1])
                    v = max(route[idx],route[idx+1])

                    for busy in range(messages[msg].size):
                        if(start_time + busy < hyper_period):
                            time[start_time + busy][(u,v)] = time[start_time + busy].get((u,v),0) + 1
                    start_time+=1

    flag = 1
    for d in time:
        for x,y in d.items():
            if(y > 1): 
                flag = 0

    return flag

def DidHeDoIt(messages,results,tolerance = 0):
    fail = 0
    for msg in range(len(results.reps)):
        for rep in range(results.reps[msg]):
            if results.amount_sent[msg][rep] != messages[msg].tl:
                fail += 1
                break
    return fail <= tolerance

num_ecu = 6
num_bridges = 0
bridge_limit = 6
link_build_cost = 2


min_period = int(1 * (1e2 // 10))
max_period = int(3 * (1e2 // 10))

min_size = 1
max_size = 1

min_tl = 2
max_tl = 2


p = []
for num_messages in range(30,90,10):
    success = 0
    for runs in tqdm(range(100)):

        M = tsn.makeInputs(num_ecu,num_bridges,num_messages,min_period,max_period,min_size,max_size,min_tl,max_tl,int(random.random() * 1e6))

        output = tsn.algo(num_ecu,num_bridges,M,bridge_limit,link_build_cost,0)
        success += int(DidHeDoIt(M,output,10))

    p.append(success/100)
print(p)






