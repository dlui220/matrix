import math

def make_translate( x, y, z ):
    pass

def make_scale( x, y, z ):
    pass
    
def make_rotX( theta ):   
    pass

def make_rotY( theta ):
    pass

def make_rotZ( theta ):
    pass

def new_matrix(rows = 4, cols = 4):
    m = []
    for c in range( cols ):
        m.append( [] )
        for r in range( rows ):
            m[c].append( 0 )
    return m

def print_matrix( matrix ):
    pass

def ident( matrix ):
    pass

def scalar_mult( matrix, x ):
    pass

#m1 * m2 -> m2
def matrix_mult( m1, m2 ):
    pass

