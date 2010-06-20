/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 The Boeing Company
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Gary Pei <guangyu.pei@boeing.com>
 */
#include "ns3/core-module.h"
#include "ns3/yans-error-rate-model.h"
#include "ns3/nist-error-rate-model.h"
#include "ns3/gnuplot.h"

#include <fstream>
#include <vector>

using namespace ns3;

int main (int argc, char *argv[])
{
  uint32_t FrameSize = 2000;
  std::ofstream yansfile ("yans-frame-success-rate.plt");
  std::ofstream nistfile ("nist-frame-success-rate.plt");
  std::vector <std::string> modes;

  modes.push_back ("OfdmRate6Mbps");
  modes.push_back ("OfdmRate9Mbps");
  modes.push_back ("OfdmRate12Mbps");
  modes.push_back ("OfdmRate18Mbps");
  modes.push_back ("OfdmRate24Mbps");
  modes.push_back ("OfdmRate36Mbps");
  modes.push_back ("OfdmRate48Mbps");
  modes.push_back ("OfdmRate54Mbps");

  CommandLine cmd;
  cmd.AddValue ("FrameSize", "The frame size", FrameSize);
  cmd.Parse (argc, argv);

  Gnuplot yansplot = Gnuplot ("yans-frame-success-rate.eps");
  Gnuplot nistplot = Gnuplot ("nist-frame-success-rate.eps");

  Ptr <YansErrorRateModel> yans = CreateObject<YansErrorRateModel> ();
  Ptr <NistErrorRateModel> nist = CreateObject<NistErrorRateModel> ();

  for (uint32_t i = 0; i < modes.size(); i++)
    {
      std::cout << modes[i] << std::endl;
      Gnuplot2dDataset yansdataset (modes[i]);
      Gnuplot2dDataset nistdataset (modes[i]);

      for (double snr = -5.0; snr <= 30.0; snr += 0.1)
        {
          double ps = yans->GetChunkSuccessRate(WifiMode(modes[i]), pow(10.0,snr/10.0), FrameSize*8);
          yansdataset.Add (snr, ps);
          ps = nist->GetChunkSuccessRate(WifiMode(modes[i]), pow(10.0,snr/10.0), FrameSize*8);
          nistdataset.Add (snr, ps);
        }

      yansplot.AddDataset (yansdataset);
      nistplot.AddDataset (nistdataset);
    }

  yansplot.SetTerminal ("postscript eps color enh \"Times-BoldItalic\"");
  yansplot.SetLegend ("SNR(dB)", "Frame Success Rate");
  yansplot.SetExtra  ("set xrange [-5:30]\n\
set yrange [0:1.2]\n\
set style line 1 linewidth 5\n\
set style line 2 linewidth 5\n\
set style line 3 linewidth 5\n\
set style line 4 linewidth 5\n\
set style line 5 linewidth 5\n\
set style line 6 linewidth 5\n\
set style line 7 linewidth 5\n\
set style line 8 linewidth 5\n\
set style increment user");
  yansplot.GenerateOutput (yansfile);
  yansfile.close ();

  nistplot.SetTerminal ("postscript eps color enh \"Times-BoldItalic\"");
  nistplot.SetLegend ("SNR(dB)", "Frame Success Rate");
  nistplot.SetExtra  ("set xrange [-5:30]\n\
set yrange [0:1.2]\n\
set style line 1 linewidth 5\n\
set style line 2 linewidth 5\n\
set style line 3 linewidth 5\n\
set style line 4 linewidth 5\n\
set style line 5 linewidth 5\n\
set style line 6 linewidth 5\n\
set style line 7 linewidth 5\n\
set style line 8 linewidth 5\n\
set style increment user");

  nistplot.GenerateOutput (nistfile);
  nistfile.close ();
}