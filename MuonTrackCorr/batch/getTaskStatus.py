import os
import sys
import argparse
import datetime
import glob
import re
from itertools import groupby

def getLog (proto, ID, silenceWarning=False):
    logs = glob.glob(proto.format(ID, '*'))
    if len(logs) == 0:
        if not silenceWarning: print ">>> No log found for job", ID
        return None
    if len(logs) > 1:
        # print ">>> Too many logs found for job", ID, ' : ', logs, 'returning last'
        if not silenceWarning: print ">>> Too many logs found for job", ID, ' (resubmitted?) , returning last'
    return logs[-1]

def getExitCode(fname, text='cmsRun finished with status'):
    f = open(fname)
    code = -888
    for line in f:
        if not '... %s' % text in line:
            continue
        code = int(re.search('... %s (\d+)' % text, line).group(1))
    return code

##############################
##### CMD line options
parser = argparse.ArgumentParser(description='Command line parser of plotting options')

parser.add_argument('--dir',          dest='folder',      help='process folder',         default=None)
parser.add_argument('--resubCmd',     dest='resubCmd',    help='print resubmit cmd',  action='store_true',   default=False)
parser.add_argument('--issueCmd',     dest='issueCmd',    help='issue resubmit cmd',  action='store_true',   default=False)
parser.add_argument('--long',         dest='short',       help='want long summary',   action='store_false',  default=True)
parser.add_argument('--flist',        dest='flist',       help='dump good files to filelist',                default=None)

args = parser.parse_args()

if not args.folder:
    print "Please set job+log folder name"

##############################

job_proto = args.folder + '/job_{0}.sh'
log_proto = args.folder + '/job_{0}.sh_{1}.stdout'

jobs_sh = glob.glob(job_proto.format('*'))
jobs_ID = [int(re.search(job_proto.format('(\d+)'), x).group(1)) for x in jobs_sh]
# print jobs_ID
# print "** Found", len(jobs_ID), 'jobs'

if len(jobs_ID) == 0:
    print "** No jobs found"
    sys.exit()

logs_txt = {ID: getLog(log_proto, ID) for ID in jobs_ID if getLog(log_proto, ID, silenceWarning=True)}
# print logs_txt

#############################

exitCodes    = []
exitCodes_cp = []
## code -999 means no log yet (unfinished?)
## code -888 means no CMSSW string found (unfinished? / crash?)
for ID in jobs_ID:
    if not ID in logs_txt:
        exitCodes.append(-999)
        exitCodes_cp.append(-999)
    else:
        exitCodes.append(getExitCode(logs_txt[ID]))
        exitCodes_cp.append(getExitCode(logs_txt[ID], text='copy done with status'))

###########################
missing    = []
unfinished = []
failed     = []
success    = []

for idx, ID in enumerate(jobs_ID):
    code = exitCodes[idx]
    code_cp = exitCodes_cp[idx]
    if   code == -999:                missing.append((ID, code, code_cp))
    elif code == -888:                unfinished.append((ID, code, code_cp))
    elif code == 0 and code_cp == 0:  success.append((ID, code, code_cp))
    else:                             failed.append((ID, code, code_cp))

# print exitCodes
print "\n***********************************************************"
print "** TOTAL JOB FOUND: ", len(jobs_ID)
print "** Success        : ", len(success) , "(%.1f%%)" % (100.*len(success)/len(jobs_ID))
print "** Failed         : ", len(failed) , "(%.1f%%)" % (100.*len(failed)/len(jobs_ID))
print "** Unfinished     : ", len(unfinished) , "(%.1f%%)" % (100.*len(unfinished)/len(jobs_ID))
print "** Missing logs   : ", len(missing) , "(%.1f%%)" % (100.*len(missing)/len(jobs_ID))
print "***********************************************************"

if not args.short:
   print '\n'
   print '** Failed jobs ID + CODE + xrdcp code, logfile'
   for val in failed:
       print '-', val[0], '+', val[1], ' + ', val[2], ' , ', logs_txt[val[0]]
   print '** Unfinished jobs ID + CODE, logfile'
   for val in unfinished:
       print '-', val[0], '+', val[1], ' , ', logs_txt[val[0]]
   print '** Missing log jobs ID'
   for val in missing:
       print '-', val[0]

### aggregate the failure causes
print "\n ** Aggregated list of failures"
groups = []
uniquekeys = []
for k, g in groupby( sorted(failed, key=lambda x : x[1]), lambda x : x[1]):
   groups.append(list(g))    # Store group iterator as a list
   uniquekeys.append(k)
for idx, uk in enumerate(uniquekeys):
    print ' -- {:.1f}% : {:}'.format(100.*len(groups[idx]) / len(failed), uk)

if args.flist:
    print '** Writing the successful files to the filelist ', args.flist
    ofile_proto = 'root://cmseos.fnal.gov//store/user/lcadamur/L1MuTrks_ntuples/{dir}/output/ntuple_{jobidx}.root'
    print '***** assuming that ntuples are staged out as: ', ofile_proto
    out_flist = open(args.flist, 'w')
    for val in success:
        ofile = ofile_proto.format(dir=args.folder.replace('jobs_', ''), jobidx=val[0])
        out_flist.write(ofile+'\n')

#######################
if args.resubCmd or args.issueCmd:
    print "\n** Resubmit commands\n"
    print "cd %s" % args.folder
    resubCmds = []
    for val in failed:
        jobscript = job_proto.format(val[0]).replace(args.folder + '/', '')
        command   = "../t3submit %s" % jobscript
        resubCmds.append(command)
    for cmd in resubCmds:
        print cmd

if args.issueCmd:
    print "\n** Issuing resub\n"
    os.chdir(args.folder)
    for cmd in resubCmds:
        os.system(cmd)


