#ifndef __COMPILER_H__
#define __COMPILER_H__

#define WRITE_ONCE(x, val)	\
    ({			    	\
     	x = val;		\
     	val;			\
    })

#endif /* !__COMPILER_H__ */
