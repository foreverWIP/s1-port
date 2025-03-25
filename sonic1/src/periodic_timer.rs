use std::{
    collections::VecDeque,
    time::{Duration, Instant},
};

pub struct PeriodicTimer {
    samples: VecDeque<f64>,
    average: f64,
    num_samples: usize,
    cur_start: Instant,
}
impl PeriodicTimer {
    pub fn new(num_samples: u8) -> Self {
        Self {
            samples: VecDeque::with_capacity(num_samples as usize),
            average: num_samples as f64,
            num_samples: num_samples as usize,
            cur_start: Instant::now(),
        }
    }

    pub fn start(&mut self) {
        self.cur_start = Instant::now();
    }

    pub fn finish(&mut self) {
        if self.samples.len() >= self.num_samples {
            self.samples.pop_front();
        }
        self.samples
            .push_back(Instant::now().duration_since(self.cur_start).as_secs_f64());
    }

    pub fn get_average_duration(&self) -> f64 {
        if self.samples.len() == 0 {
            return 0.0;
        }
        self.samples.iter().sum::<f64>() / self.samples.len() as f64
    }

    pub fn get_average_periodicity(&mut self) -> f64 {
        if self.samples.len() == 0 {
            return 0.0;
        }
        let last_sample = *self.samples.back().unwrap();
        let mut frames_in_second = 0.0;
        for i in 0..self.samples.len() {
            if (last_sample - self.samples[self.samples.len() - i - 1]) >= 1.0 {
                break;
            }
            frames_in_second += 1.0;
        }
        let alpha = 0.9;
        self.average = self.average * alpha + (1.0 - alpha) * frames_in_second;
        self.average
    }
}
