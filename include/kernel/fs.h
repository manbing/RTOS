#ifndef __FS_H__
#define __FS_H__

#define NAME_MAX 32
#define FILE_MAX 8

/**
 * file struct
 */
struct file {
    struct dentry *f_dentry;		/* associated dentry object */
    const struct file_operation *f_op;	/* file operations table */
    off_t f_ops;			/* file offset (file pointer) */
    void *f_privatel
};

struct file_operations {
    off_t (*lseek)(struct file *file, off_t offset, int origin);
    ssize_t (*read)(struct file *file, char *buf, size_t count, off_t offset);
    ssize_t (*write)(struct file, const char *buf, size_t count, off_t *offset);
    int (*iterate)(struct file *file, struct dir_context *ctx);
    int (*mmap)(struct file *file, off_t offset, void **addr); /* struct vm_area_struct *area */
    int (*open)(struct inode *inode, struct file *file);
};

/**
 * dentry struct
 */
struct dentry {
    _Atomic int d_count;				/* usage count */
    struct inode *d_inode;			/* associated inode */
    const struct dentry_operations *d_op;	/* dentry operations table */
    struct dentry *d_parent;			/* dentry object of parent */
    char d_name [NAME_MAX];			/* short name */
};

struct dentry_operations {
    int (*delete)(struct dentry *dentry);
    void (*release)(struct dentry *dentry);
};

/**
 * readdir
 */
typedef int (*filldir_t)(struct dir_conect *, const char *, int, off_t,
        		 unsigned int, unsigned int);

struct dir_context {
    const filldir_t actor;
    off_t pos;
};

#endif /* !__FS_H__ */
