/*
 * libiio - Library for interfacing industrial I/O (IIO) devices
 *
 * Copyright (C) 2014 Analog Devices, Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * */

#ifndef __IIO_PRIVATE_H__
#define __IIO_PRIVATE_H__

/* Include public interface */
#pragma GCC visibility push(default)
#include "iio.h"
#pragma GCC visibility pop

#include <stdbool.h>

#define BIT_MASK(bit) (1 << ((bit) % 32))
#define BIT_WORD(bit) ((bit) / 32)
#define TEST_BIT(addr, bit) (!!(*(((uint32_t *) addr) + BIT_WORD(bit)) \
		& BIT_MASK(bit)))
#define SET_BIT(addr, bit) \
	*(((uint32_t *) addr) + BIT_WORD(bit)) |= BIT_MASK(bit)
#define CLEAR_BIT(addr, bit) \
	*(((uint32_t *) addr) + BIT_WORD(bit)) &= ~BIT_MASK(bit)

enum iio_context_type {
	IIO_LOCAL_CONTEXT,
	IIO_DUMMY_CONTEXT,
	IIO_NETWORK_CONTEXT,
};

enum iio_modifier {
	IIO_NO_MOD,
	IIO_MOD_X,
	IIO_MOD_Y,
	IIO_MOD_Z,
	IIO_MOD_LIGHT_BOTH,
	IIO_MOD_LIGHT_IR,
	IIO_MOD_ROOT_SUM_SQUARED_X_Y,
	IIO_MOD_SUM_SQUARED_X_Y_Z,
	IIO_MOD_LIGHT_CLEAR,
	IIO_MOD_LIGHT_RED,
	IIO_MOD_LIGHT_GREEN,
	IIO_MOD_LIGHT_BLUE,
};

struct iio_backend_ops {
	ssize_t (*read)(const struct iio_device *dev, void *dst, size_t len);
	ssize_t (*write)(const struct iio_device *dev,
			const void *src, size_t len);
	int (*open)(const struct iio_device *dev, uint32_t *mask, size_t words);
	int (*close)(const struct iio_device *dev);

	int (*channel_enable)(struct iio_channel *channel);
	int (*channel_disable)(struct iio_channel *channel);

	unsigned int (*get_devices_count)(const struct iio_context *ctx);
	struct iio_device * (*get_device)(const struct iio_context *ctx,
			unsigned int id);

	ssize_t (*read_device_attr)(const struct iio_device *dev,
			const char *attr, char *dst, size_t len);
	ssize_t (*write_device_attr)(const struct iio_device *dev,
			const char *attr, const char *src);
	ssize_t (*read_channel_attr)(const struct iio_channel *chn,
			const char *attr, char *dst, size_t len);
	ssize_t (*write_channel_attr)(const struct iio_channel *chn,
			const char *attr, const char *src);

	int (*get_trigger)(const struct iio_device *dev,
			const struct iio_device **trigger);
	int (*set_trigger)(const struct iio_device *dev,
			const struct iio_device *trigger);

	void (*shutdown)(struct iio_context *ctx);
};

struct iio_context_pdata;
struct iio_device_pdata;
struct iio_channel_pdata;

struct iio_context {
	struct iio_context_pdata *pdata;
	const struct iio_backend_ops *ops;
	const char *name;

	struct iio_device **devices;
	unsigned int nb_devices;
};

struct iio_data_format {
	unsigned int length;
	unsigned int bits;
	unsigned int shift;
	bool with_scale, is_signed, is_be;
	double scale;
};

struct iio_channel {
	struct iio_device *dev;
	struct iio_channel_pdata *pdata;
	void *userdata;

	bool is_output;
	enum iio_modifier modifier;
	struct iio_data_format format;
	char *name, *id;
	long index;
	bool enabled;

	char **attrs;
	unsigned int nb_attrs;
};

struct iio_device {
	const struct iio_context *ctx;
	struct iio_device_pdata *pdata;
	void *userdata;

	char *name, *id;

	char **attrs;
	unsigned int nb_attrs;

	struct iio_channel **channels;
	unsigned int nb_channels;
};

void iio_msg(enum iio_debug_level level, const char *msg);
void free_channel(struct iio_channel *chn);
void free_device(struct iio_device *dev);

char *iio_channel_get_xml(const struct iio_channel *chn, size_t *len);
char *iio_device_get_xml(const struct iio_device *dev, size_t *len);

void iio_context_init_channels(const struct iio_context *ctx);

#endif /* __IIO_PRIVATE_H__ */
