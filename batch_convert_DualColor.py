"""
Batch convert a folder using imagemagick convert with a python wrapper. 
Arguments: 
1 path to image files to convert
2 output folder
3 output format eg jpg, png etc.
4 output file basename
5 optional: transpose the image - rotate 90 deg counterclockwise.
"""

import os,sys,re
import subprocess


def natural_sort(liste):
    """Natural sort to have frames in right order."""
    convert = lambda text: int(text) if text.isdigit() else text.lower()
    alphanum_key = lambda key: [convert(c) for c in re.split('([0-9]+)', key)]
    return sorted(liste, key = alphanum_key)

inpath = sys.argv[1]
outpath = sys.argv[2]
formt =  sys.argv[3]
basename = outpath#sys.argv[4]
transpose = False
if len(sys.argv)>4:
    transpose = bool(sys.argv[4])

print "Creating folder 1: ", basename
os.system('mkdir %s_1'%basename)
print "Creating folder 2: ", basename
os.system('mkdir %s_2'%basename)

print "ATTENTION: Deletes files in source folder!!!!!!"
for (dirpath, dirnames, filenames) in os.walk(inpath):
    filenames = natural_sort(filenames)
    for index,filename in enumerate(filenames):
        if index%2==0:
            outfolder = '%s_2'%basename
        else:
            outfolder = '%s_1'%basename
        new_name = "%s_%s.%s"%(basename,filename.split("_")[-1].split(".")[-2],formt)
        #print new_name, os.path.join(dirpath, filename),os.path.join(outpath,new_name)
        if transpose:
            os.system('gm convert -rotate -90 %s %s'%(os.path.join(dirpath, filename), os.path.join(outfolder,new_name)))
        else:
            os.system('gm convert "%s" %s'%(os.path.join(dirpath, filename), os.path.join(outfolder,new_name)))
        if os.path.exists(os.path.join(outfolder,new_name)):
            print 'ok'
            #os.system('del "%s"'%(os.path.join(dirpath, filename)))
        else:
            print "Have you made a folder????"
            break
        if index%1000==0:
            print index
