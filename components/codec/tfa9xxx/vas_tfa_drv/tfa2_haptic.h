/*
 * Copyright  2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TFA2_HAPTIC_H_
#define TFA2_HAPTIC_H_

#include "tfa2_dev.h"

#define TFA2_HAPTIC_FP_INT(value, shift)  ((value) >> (shift))
#define TFA2_HAPTIC_FP_FRAC(value, shift) ((((value) & ((1 << (shift)) - 1)) * 1000) >> (shift))

int tfa2_dev_start_hapticboost(struct tfa2_device *tfa);
int tfa2_hap_calibrate(struct tfa2_device *tfa);
int tfa2_hap_recalculate(struct tfa2_device *tfa, int object);
int tfa2_hap_load_data(struct tfa2_device *tfa);
int tfa2_hap_sequencer(struct tfa2_device *tfa, struct tfa2_sequence *seq);
int tfa2_hap_get_sequencer_duration(struct tfa2_device *tfa, struct tfa2_sequence *seq);
int tfa2_hap_sequencer_object(struct tfa2_device *tfa, int virtual_obj);
void tfa2_hap_sequencer_destroy(struct tfa2_sequence *seq);
int tfa2_hap_cnt_sequencer_count(nxpTfaContainer_t *cnt, int devidx);
int tfa2_hap_cnt_get_sequencer(nxpTfaContainer_t *cnt, int devidx, int seqidx, struct tfa2_sequence *seq);
int tfa2_haptic_obj0_wait_finish(struct i2c_client *client);
void tfa2_haptic_obj_get(struct haptic_data *data, int idx);
int tfa2_haptic_get_duration(struct tfa2_device *tfa, int index);
enum tfa_haptic_object_type tfa2_haptic_object_type(struct haptic_data *data, int index);
int tfa2_haptic_parse_value(struct haptic_data *data, int value);
int tfa2_haptic_start(struct tfa2_device *tfa, struct haptic_data *data, int index);
int tfa2_haptic_start_object(struct i2c_client *client, struct haptic_data *data, int index);
int tfa2_haptic_stop(struct tfa2_device *tfa, struct haptic_data *data, int index);
int tfa2_haptic_read_f0(struct i2c_client *client, int *p_value);
int tfa2_haptic_disable_f0_trc(struct i2c_client *client, int disable);
void tfa2_haptic_set_version_check(int check);
int tfa2_haptic_update_duration(struct haptic_data *data, int duration);
int tfa2_hap_patch_version(struct tfa2_device *tfa, char *string);
void tfa2_hap_save_haptic_cache(struct tfa2_device *tfa, struct tfa2_sequence *seq);
void tfa2_hap_test_restore_haptic_cache(struct tfa2_device *tfa, struct tfa2_sequence *seq);

#endif /* TFA2_HAPTIC_H_ */
