#include "GiveTitle.h"

namespace GiveTitle {

/*******************************************************************************************************************
Cycling '74 License for Max-Generated Code for Export
Copyright (c) 2016 Cycling '74
The code that Max generates automatically and that end users are capable of exporting and using, and any
  associated documentation files (the “Software”) is a work of authorship for which Cycling '74 is the author
  and owner for copyright purposes.  A license is hereby granted, free of charge, to any person obtaining a
  copy of the Software (“Licensee”) to use, copy, modify, merge, publish, and distribute copies of the Software,
  and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The Software is licensed to Licensee only for non-commercial use. Users who wish to make commercial use of the
  Software must contact the copyright owner to determine if a license for commercial use is available, and the
  terms and conditions for same, which may include fees or royalties. For commercial use, please send inquiries
  to licensing (at) cycling74.com.  The determination of whether a use is commercial use or non-commercial use is based
  upon the use, not the user. The Software may be used by individuals, institutions, governments, corporations, or
  other business whether for-profit or non-profit so long as the use itself is not a commercialization of the
  materials or a use that generates or is intended to generate income, revenue, sales or profit.
The above copyright notice and this license shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
  THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*******************************************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Data m_main_19;
	Data m_stutter_21;
	Delta __m_delta_36;
	PlusEquals __m_pluseq_37;
	Rate __m_rate_35;
	int __exception;
	int vectorsize;
	t_sample m_button_20;
	t_sample m_ctrl_17;
	t_sample m_ctrl_18;
	t_sample m_gate_22;
	t_sample __m_count_24;
	t_sample m_ctrl_16;
	t_sample __m_carry_32;
	t_sample m_sw_23;
	t_sample __m_count_30;
	t_sample __m_carry_26;
	t_sample __m_count_38;
	t_sample m_ctrl_15;
	t_sample m_ctrl_13;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_ctrl_14;
	t_sample m_history_6;
	t_sample m_history_8;
	t_sample m_ctrl_12;
	t_sample m_history_7;
	t_sample m_sw_11;
	t_sample m_history_9;
	t_sample m_history_10;
	t_sample __m_latch_39;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_sw_11 = ((int)0);
		m_ctrl_12 = ((int)0);
		m_ctrl_13 = ((int)0);
		m_ctrl_14 = ((int)0);
		m_ctrl_15 = ((int)0);
		m_ctrl_16 = ((int)0);
		m_ctrl_17 = ((int)0);
		m_ctrl_18 = ((int)0);
		m_main_19.reset("main", ((int)384000), ((int)2));
		m_button_20 = ((int)0);
		m_stutter_21.reset("stutter", ((int)384000), ((int)2));
		m_gate_22 = ((int)0);
		m_sw_23 = ((int)0);
		__m_count_24 = 0;
		__m_carry_26 = 0;
		__m_count_30 = 0;
		__m_carry_32 = 0;
		__m_rate_35.reset();
		__m_delta_36.reset(0);
		__m_pluseq_37.reset(0);
		__m_count_38 = 0;
		__m_latch_39 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		t_sample * __out6 = __outs[5];
		t_sample * __out7 = __outs[6];
		t_sample * __out8 = __outs[7];
		t_sample * __out9 = __outs[8];
		t_sample * __out10 = __outs[9];
		t_sample * __out11 = __outs[10];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) || (__out10 == 0) || (__out11 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		int main_dim = m_main_19.dim;
		int main_channels = m_main_19.channels;
		int main_dim_290 = main_dim;
		int dim_270 = main_dim;
		int stutter_dim = m_stutter_21.dim;
		int stutter_channels = m_stutter_21.channels;
		int irange_543 = (dim_270 - ((int)1));
		int or_354 = (m_gate_22 || m_button_20);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out4 = ((int)0);
			t_sample out5 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out3 = ((int)0);
			t_sample out8 = ((int)0);
			t_sample out10 = ((int)0);
			t_sample out11 = samplerate;
			__m_count_24 = (((int)0) ? 0 : (fixdenorm(__m_count_24 + ((int)1))));
			int carry_25 = 0;
			if ((((int)0) != 0)) {
				__m_count_24 = 0;
				__m_carry_26 = 0;
				
			} else if (((main_dim_290 > 0) && (__m_count_24 >= main_dim_290))) {
				int wraps_27 = (__m_count_24 / main_dim_290);
				__m_carry_26 = (__m_carry_26 + wraps_27);
				__m_count_24 = (__m_count_24 - (wraps_27 * main_dim_290));
				carry_25 = 1;
				
			};
			int counter_283 = __m_count_24;
			int counter_284 = carry_25;
			int counter_285 = __m_carry_26;
			int index_wrap_28 = ((counter_283 < 0) ? ((main_dim - 1) + ((counter_283 + 1) % main_dim)) : (counter_283 % main_dim));
			m_main_19.write(in1, index_wrap_28, 0);
			int index_wrap_29 = ((counter_283 < 0) ? ((main_dim - 1) + ((counter_283 + 1) % main_dim)) : (counter_283 % main_dim));
			// samples main channel 1;
			t_sample sample_main_286 = m_main_19.read(index_wrap_29, 0);
			t_sample index_main_287 = counter_283;
			t_sample mix_532 = (m_history_10 + (((t_sample)0.0019634941468452) * (m_ctrl_18 - m_history_10)));
			t_sample mix_326 = mix_532;
			t_sample mix_533 = (m_history_9 + (((t_sample)0.0019634941468452) * (mix_326 - m_history_9)));
			t_sample mix_324 = mix_533;
			t_sample mix_534 = (m_history_8 + (((t_sample)0.0019634941468452) * (mix_324 - m_history_8)));
			t_sample mix_322 = mix_534;
			t_sample gen_338 = mix_322;
			t_sample history_327_next_329 = fixdenorm(mix_326);
			t_sample history_325_next_330 = fixdenorm(mix_324);
			t_sample history_323_next_331 = fixdenorm(mix_322);
			t_sample mix_535 = (m_history_7 + (((t_sample)0.0019634941468452) * (m_ctrl_14 - m_history_7)));
			t_sample mix_469 = mix_535;
			t_sample mix_536 = (m_history_6 + (((t_sample)0.0019634941468452) * (mix_469 - m_history_6)));
			t_sample mix_470 = mix_536;
			t_sample mix_537 = (m_history_5 + (((t_sample)0.0019634941468452) * (mix_470 - m_history_5)));
			t_sample mix_468 = mix_537;
			t_sample gen_337 = mix_468;
			t_sample history_327_next_474 = fixdenorm(mix_469);
			t_sample history_325_next_473 = fixdenorm(mix_470);
			t_sample history_323_next_472 = fixdenorm(mix_468);
			t_sample sub_541 = (gen_337 - ((int)0));
			t_sample scale_538 = ((safepow((sub_541 * ((t_sample)1)), ((int)1)) * ((int)383999)) + ((int)1));
			__m_count_30 = (((int)0) ? 0 : (fixdenorm(__m_count_30 + ((int)1))));
			int carry_31 = 0;
			if ((((int)0) != 0)) {
				__m_count_30 = 0;
				__m_carry_32 = 0;
				
			} else if (((scale_538 > 0) && (__m_count_30 >= scale_538))) {
				int wraps_33 = (__m_count_30 / scale_538);
				__m_carry_32 = (__m_carry_32 + wraps_33);
				__m_count_30 = (__m_count_30 - (wraps_33 * scale_538));
				carry_31 = 1;
				
			};
			int counter_263 = __m_count_30;
			int counter_264 = carry_31;
			int counter_265 = __m_carry_32;
			int index_clamp_34 = ((counter_263 < 0) ? 0 : ((counter_263 > stutter_dim) ? stutter_dim : counter_263));
			m_stutter_21.write(sample_main_286, index_clamp_34, 0);
			int sub_545 = (counter_263 - ((int)1));
			t_sample scale_542 = ((safepow(safediv(sub_545, irange_543), ((int)1)) * ((int)1)) + ((int)0));
			t_sample rate_275 = __m_rate_35.perform_off(scale_542, ((int)1));
			t_sample out9 = rate_275;
			t_sample out7 = rate_275;
			t_sample clamp_249 = ((scale_538 <= ((int)96000)) ? ((int)96000) : ((scale_538 >= ((int)384000)) ? ((int)384000) : scale_538));
			int delta_350 = __m_delta_36(or_354);
			int gtep_349 = ((delta_350 >= ((int)1)) ? delta_350 : 0);
			t_sample plusequals_348 = __m_pluseq_37.post(gtep_349, m_history_4, 0);
			int eq_346 = (plusequals_348 == ((int)2));
			__m_count_38 = (m_history_4 ? 0 : (fixdenorm(__m_count_38 + plusequals_348)));
			t_sample counter_343 = __m_count_38;
			int counter_344 = ((int)0);
			int counter_345 = ((int)0);
			__m_latch_39 = ((eq_346 != 0) ? counter_343 : __m_latch_39);
			t_sample latch_342 = __m_latch_39;
			t_sample history_347_next_351 = fixdenorm(eq_346);
			t_sample mix_546 = (m_history_3 + (((t_sample)0.0019634941468452) * (m_ctrl_12 - m_history_3)));
			t_sample mix_484 = mix_546;
			t_sample mix_547 = (m_history_2 + (((t_sample)0.0019634941468452) * (mix_484 - m_history_2)));
			t_sample mix_482 = mix_547;
			t_sample mix_548 = (m_history_1 + (((t_sample)0.0019634941468452) * (mix_482 - m_history_1)));
			t_sample mix_483 = mix_548;
			t_sample gen_336 = mix_483;
			t_sample history_327_next_487 = fixdenorm(mix_484);
			t_sample history_325_next_486 = fixdenorm(mix_482);
			t_sample history_323_next_490 = fixdenorm(mix_483);
			t_sample add_250 = (gen_336 + ((t_sample)0.001));
			t_sample mul_254 = (add_250 * ((int)16));
			t_sample ceil_253 = ceil(mul_254);
			t_sample div_256 = safediv(latch_342, ceil_253);
			t_sample div_251 = safediv(div_256, clamp_249);
			t_sample mod_255 = safemod(rate_275, div_251);
			double sample_index_40 = (mod_255 * (stutter_dim - 1));
			int index_trunc_41 = fixnan(floor(sample_index_40));
			double index_fract_42 = (sample_index_40 - index_trunc_41);
			int index_trunc_43 = (index_trunc_41 + 1);
			int index_clamp_44 = ((index_trunc_41 < 0) ? 0 : ((index_trunc_41 > stutter_dim) ? stutter_dim : index_trunc_41));
			int index_clamp_45 = ((index_trunc_43 < 0) ? 0 : ((index_trunc_43 > stutter_dim) ? stutter_dim : index_trunc_43));
			// phase stutter channel 1;
			double read_stutter_46 = m_stutter_21.read(index_clamp_44, 0);
			double read_stutter_47 = m_stutter_21.read(index_clamp_45, 0);
			double readinterp_48 = linear_interp(index_fract_42, read_stutter_46, read_stutter_47);
			t_sample sample_stutter_260 = readinterp_48;
			t_sample index_stutter_261 = sample_index_40;
			t_sample mul_281 = (mod_255 * ((int)2));
			t_sample sub_280 = (mul_281 - ((int)1));
			t_sample cos_279 = cos(sub_280);
			t_sample sub_278 = (cos_279 - ((t_sample)0.5));
			t_sample mul_277 = (sub_278 * ((int)10));
			t_sample clamp_276 = ((mul_277 <= ((int)0)) ? ((int)0) : ((mul_277 >= ((int)1)) ? ((int)1) : mul_277));
			t_sample mul_246 = (sample_stutter_260 * clamp_276);
			t_sample mix_549 = (sample_main_286 + (gen_338 * (mul_246 - sample_main_286)));
			t_sample out2 = mix_549;
			t_sample out1 = mix_549;
			m_history_10 = history_327_next_329;
			m_history_8 = history_323_next_331;
			m_history_9 = history_325_next_330;
			m_history_7 = history_327_next_474;
			m_history_5 = history_323_next_472;
			m_history_6 = history_325_next_473;
			m_history_4 = history_347_next_351;
			m_history_3 = history_327_next_487;
			m_history_1 = history_323_next_490;
			m_history_2 = history_325_next_486;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			(*(__out10++)) = out10;
			(*(__out11++)) = out11;
			
		};
		return __exception;
		
	};
	inline void set_sw2(t_param _value) {
		m_sw_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl3(t_param _value) {
		m_ctrl_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl7(t_param _value) {
		m_ctrl_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl5(t_param _value) {
		m_ctrl_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl4(t_param _value) {
		m_ctrl_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl6(t_param _value) {
		m_ctrl_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl2(t_param _value) {
		m_ctrl_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_ctrl1(t_param _value) {
		m_ctrl_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_main(void * _value) {
		m_main_19.setbuffer(_value);
	};
	inline void set_button(t_param _value) {
		m_button_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_stutter(void * _value) {
		m_stutter_21.setbuffer(_value);
	};
	inline void set_gate(t_param _value) {
		m_gate_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 11;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 13; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "led3", "led4", "out7", "out8", "out9", "out10", "out11" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_button(value); break;
		case 1: self->set_ctrl1(value); break;
		case 2: self->set_ctrl2(value); break;
		case 3: self->set_ctrl3(value); break;
		case 4: self->set_ctrl4(value); break;
		case 5: self->set_ctrl5(value); break;
		case 6: self->set_ctrl6(value); break;
		case 7: self->set_ctrl7(value); break;
		case 8: self->set_gate(value); break;
		case 9: self->set_main(ref); break;
		case 10: self->set_stutter(ref); break;
		case 11: self->set_sw1(value); break;
		case 12: self->set_sw2(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_button_20; break;
		case 1: *value = self->m_ctrl_18; break;
		case 2: *value = self->m_ctrl_17; break;
		case 3: *value = self->m_ctrl_12; break;
		case 4: *value = self->m_ctrl_15; break;
		case 5: *value = self->m_ctrl_14; break;
		case 6: *value = self->m_ctrl_16; break;
		case 7: *value = self->m_ctrl_13; break;
		case 8: *value = self->m_gate_22; break;
		
		
		case 11: *value = self->m_sw_23; break;
		case 12: *value = self->m_sw_11; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(13 * sizeof(ParamInfo));
	self->__commonstate.numparams = 13;
	// initialize parameter 0 ("m_button_20")
	pi = self->__commonstate.params + 0;
	pi->name = "button";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_button_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_ctrl_18")
	pi = self->__commonstate.params + 1;
	pi->name = "ctrl1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_ctrl_17")
	pi = self->__commonstate.params + 2;
	pi->name = "ctrl2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_ctrl_12")
	pi = self->__commonstate.params + 3;
	pi->name = "ctrl3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_ctrl_15")
	pi = self->__commonstate.params + 4;
	pi->name = "ctrl4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_ctrl_14")
	pi = self->__commonstate.params + 5;
	pi->name = "ctrl5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_ctrl_16")
	pi = self->__commonstate.params + 6;
	pi->name = "ctrl6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_ctrl_13")
	pi = self->__commonstate.params + 7;
	pi->name = "ctrl7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_ctrl_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_gate_22")
	pi = self->__commonstate.params + 8;
	pi->name = "gate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_main_19")
	pi = self->__commonstate.params + 9;
	pi->name = "main";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_stutter_21")
	pi = self->__commonstate.params + 10;
	pi->name = "stutter";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_23")
	pi = self->__commonstate.params + 11;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_sw_11")
	pi = self->__commonstate.params + 12;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // GiveTitle::
