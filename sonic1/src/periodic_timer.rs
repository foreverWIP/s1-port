use std::{
    collections::VecDeque,
    time::{Duration, Instant},
};

pub struct PeriodicTimer {
    samples: VecDeque<Instant>,
    average: f64,
    num_samples: usize,
}
impl PeriodicTimer {
    pub fn new(num_samples: u8) -> Self {
        Self {
            samples: VecDeque::with_capacity(num_samples as usize),
            average: num_samples as f64,
            num_samples: num_samples as usize,
        }
    }

    pub fn poll(&mut self) {
        if self.samples.len() >= self.num_samples {
            self.samples.pop_front();
        }
        self.samples.push_back(Instant::now());
    }

    pub fn get_average(&mut self) -> f64 {
        if self.samples.len() == 0 {
            return 0.0;
        }
        let last_sample = *self.samples.back().unwrap();
        let second_before = last_sample - Duration::from_secs(1);
        let mut frames_in_second = 0.0;
        for sample in &self.samples {
            if *sample >= second_before {
                frames_in_second += 1.0;
            }
        }
        let alpha = 0.9;
        self.average = self.average * alpha + (1.0 - alpha) * frames_in_second;
        self.average
    }
}
