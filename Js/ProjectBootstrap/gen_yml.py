d={
    'foo':'bar',
    'nest':{
        'one':1,
        'two':2
    },
    'super-nest':{
        'nest':{
            'hest':12
        },
        'foo':'oid',
        'h':['hello'],
        'liawst':['date'],
        'nestns':[ {'make':'me','happy':['now']}]
    }
}

def dict2yml(d,indent=0,tab='  '):
    res = ""
    for key,val in d.items():
        res+= indent*tab
        res+=key+':'
        if  type(val)==dict:
            res+='\n'
            res+=dict2yml(val,
                          indent=indent+1,
                          tab=tab)
        else:
            res+= str(val)
            res+= '\n'
    return res

def dict2json(d,indent=0,tab='  ',mapper=None):
    res = ""
    if  type(d)==dict:
        res+='\n'+indent*tab+'{\n'
        for key,val in d.items():
            v = dict2json(val,
                           indent=indent+1,
                           tab=tab,
                           mapper=mapper
                          )
            res+= indent*tab
            res+='"%s":%s,\n'%(key,v)
        res+=indent*tab+'}'
        return res
    elif mapper:
        try:
            v = mapper(d)
            if v:
                return v
        except:
            pass
    if type(d)==str:
        res+= '"%s"'%(d)
    elif type(d)==list:
        if len(d)>1:
            raise Exception("Only len(1) lists allowed!")
        v = dict2json(d[0],
                       indent=indent+1,
                       tab=tab,
                       mapper=mapper
                      )
        res+= '[ %s ]'%v
    else:
        res+= str(d)
    return res

def mongoose_mapper(val):
    table={
        'date': 'Date',
        'oid':  'Schema.Types.ObjectId',
        'str':  'String',
        'int':  'Number',
        'bool': 'Boolean'
    }
    return table.get(val)

def dict2mongoose(d):
    res= """
var mongoose = require('mongoose');
var Schema = mongoose.Schema;
%(name)sSchema = Schema(
%(schema)s
,{collection: '%(name)s'}
);

module.exports = {
    %(name)s:mongoose.model( %(name)sSchema ) 
}
"""%{
    'name':'Test',
    'schema': dict2json(d,mapper=mongoose_mapper)
}
    return res

#print(dict2yml(d))
#print(dict2json(d))
#print(dict2json(d,mapper=mongoose_mapper))
print(dict2mongoose(d))
