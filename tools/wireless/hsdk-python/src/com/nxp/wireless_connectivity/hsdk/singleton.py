'''
* Copyright 2014-2015 Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
'''

known_instances = {}


def singleton(decorated_class):
    """
    Class decorator to make it a singleton.

    @return: a new or already existing instance of a class
    """

    def decorator(*args, **kwargs):

        # do not index by Protocol and FsciAckPolicy
        protocol = kwargs.pop('protocol', None)
        ack_policy = kwargs.pop('ack_policy', None)

        # str(kwargs) resolves TypeError: unhashable type: 'dict'
        instance_id = (decorated_class, args, str(kwargs))

        # but add back Protocol and FsciAckPolicy to kwargs
        if protocol is not None:
            kwargs['protocol'] = protocol
        if ack_policy is not None:
            kwargs['ack_policy'] = ack_policy

        if instance_id not in known_instances:
            known_instances[instance_id] = decorated_class(*args, **kwargs)

        return known_instances[instance_id]

    return decorator
