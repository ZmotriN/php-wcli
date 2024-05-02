<?php

class CLIProgressBar
{

    const DEFAULT_OPTIONS = [
        'color_pourcentage' => Yellow | Bright,
        'color_label' => Grey,
        'color_background' => Black,
        'color_progress' => Red | Bright,
        'color_progress_text' => White | Bright,
        'color_end' => Aqua,
        'color_end_text' => White | Bright,
        'color_done' => Green,
        'color_done_text' => White,
        'label' => null,
        'label_size' => null,
        'estimate' => true,
        'pourcentage' => true,
        'size' => null,
    ];


    private $x = 0;
    private $y = 0;
    private $timer = 0;
    private $options = [];


    public function __construct($x = null, $y = null, array $options = [])
    {
        list($cx, $cy) = wcli_get_cursor_position();
        if (is_array($x)) {
            $options = $x;
            $x = $cx;
        } elseif (is_numeric($x));
        else $x = $cx;

        if (is_array($y)) {
            $options = $y;
            $y = $cy;
        } elseif (is_numeric($y));
        else $y = $cy;

        $this->x = $x;
        $this->y = $y;

        $this->options = array_merge(self::DEFAULT_OPTIONS, $options);

        if (!empty($this->options['label']) && empty($this->options['label_size']))
            $this->options['label_size'] = strlen($this->options['label']) + 1;

        if(is_null($this->options['size'])) {
            list($bw, $bh) = wcli_get_buffer_size();
            $this->options['size'] = $bw - 1;
        }

        $this->draw();
    }


    public function __get($v)
    {
        switch ($v) {
            default:
                return in_array($v, $this->options) ? $this->options[$v] : null;
        }
    }


    public function draw($progress = 0, $done = 0, $text = null)
    {
        if ($progress == 0 || $this->timer == 0) {
            $this->timer = microtime(true);
        }

        $c = $this->x;
        $size = $this->size;

        if ($this->pourcentage) $size -= 8;

        if ($this->label) {
            $label = substr(str_pad($this->label, $this->label_size), 0, $this->label_size);
            wcli_print($label, $c, $this->y, $this->color_label);
            $size -= strlen($label);
            $c += strlen($label);
        }

        if (!$text && $this->estimate) {
            if ($progress > 0 && $progress < 1 && !$done) {
                $t = microtime(1) - $this->timer;
                $eta = $t / $progress;
                if ($stime = self::str_duration($eta - $t)) {
                    $text = $stime;
                }
            }
        }

        $text = str_pad($text ?? '', $size, ' ', STR_PAD_BOTH);
        $t1_size = round($progress * $size);
        $t2_size = $size - $t1_size;

        $t1 = substr($text, 0, $t1_size);
        $t2 = substr($text, $t1_size, $t2_size);

        $color = White | Bright;
        if ($done) {
            $bgcolor = $this->color_done;
            $color = $this->color_done_text;
        } elseif ($progress == 1) {
            $bgcolor = $this->color_end;
            $color = $this->color_end_text;
        } else $bgcolor = $this->color_progress;

        wcli_print($t1, $c, $this->y, $color, $bgcolor);
        $size -= strlen($t1);
        $c += strlen($t1);

        wcli_print($t2, $c, $this->y, $color, $this->color_background);
        $size -= strlen($t2);
        $c += strlen($t2);


        if ($this->pourcentage) {
            wcli_print('|' . ' ', $c, $this->y, White | Bright);
            $c += 2;
            $pour = substr(sprintf('%0.3f', $progress * 100), 0, 5) . '%';
            wcli_print($pour, $c, $this->y, $this->color_pourcentage);
        }
    }


    private static function str_duration($time)
    {
        $str = '';
        $time = round($time, 0);
        $years = floor($time / (60 * 60 * 24 * 365));
        $time %= 60 * 60 * 24 * 365;
        $weeks = floor($time / (60 * 60 * 24 * 7));
        $time %= 60 * 60 * 24 * 7;
        $days = floor($time / (60 * 60 * 24));
        $time %= 60 * 60 * 24;
        $hrs = floor($time / (60 * 60));
        $time %= 60 * 60;
        $mins = floor($time / 60);
        $secs = $time % 60;
        if ($years >= 1) {
            $str .= ($str ? ', ' : '') . $years . ' year' . ($years > 1 ? 's' : '');
        }
        if ($weeks >= 1) {
            $str .= ($str ? ', ' : '') . $weeks . ' week' . ($weeks > 1 ? 's' : '');
        }
        if ($days >= 1) {
            $str .= ($str ? ', ' : '') . $days . ' day' . ($days > 1 ? 's' : '');
        }
        if ($hrs >= 1) {
            $str .= ($str ? ', ' : '') . $hrs . ' hour' . ($hrs > 1 ? 's' : '');
        }
        if ($mins >= 1) {
            $str .= ($str ? ', ' : '') . $mins . ' min' . ($mins > 1 ? 's' : '');
        }
        if ($secs >= 1) {
            $str .= ($str ? ', ' : '') . $secs . ' sec' . ($secs > 1 ? 's' : '');
        }
        return $str;
    }
}
